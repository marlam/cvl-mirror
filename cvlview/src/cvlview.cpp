/*
 * cvlview.cpp
 *
 * This file is part of cvlview, an image viewer using the CVL library.
 *
 * Copyright (C) 2007  Martin Lambers <marlam@marlam.de>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <climits>
#include <cstdio>

#include <GL/gl.h>

#include <QtCore>
#include <QCoreApplication>
#include <QApplication>
#include <QClipboard>
#include <QMainWindow>
#include <QWidget>
#include <QToolBar>
#include <QToolBox>
#include <QIcon>
#include <QGridLayout>
#include <QToolBox>
#include <QMenuBar>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>

#include "err.h"
#include "conf.h"

#include "image_info.h"
#include "channel_selector.h"
#include "channel_info.h"
#include "viewpoint_selector.h"
#include "range_selector.h"
#include "gamma_selector.h"
#include "pseudocolor_selector.h"
#include "view_area.h"
#include "pixel_info.h"
#include "cvlview.h"


CVLView::CVLView()
{
    setWindowTitle(PACKAGE_NAME);
    setWindowIcon(QIcon(":appicon.png"));
    _conf_file_name = mh_get_apprcpath(PACKAGE_NAME);
    _conf = new Conf();
    try
    {
	_conf->load(_conf_file_name);
    }
    catch (err e) {}
    _last_open_dir = QDir(_conf->get("session-last-open-dir", qPrintable(QDir::homePath())));
    _last_save_dir = QDir(_conf->get("session-last-save-dir", qPrintable(QDir::homePath())));
    _frame = NULL;

    /* Restore window geometry */

    QPoint pos;
    QSize size;
    pos.setX(_conf->get("session-mainwindow-x", 0, INT_MAX, 0));
    pos.setY(_conf->get("session-mainwindow-y", 0, INT_MAX, 0));
    size.setWidth(_conf->get("session-mainwindow-width", 1, INT_MAX, 1));
    size.setHeight(_conf->get("session-mainwindow-height", 1, INT_MAX, 1));
    resize(size);
    move(pos);
    if (_conf->get("session-mainwindow-maximized", false))
	showMaximized();

    /* Create widgets */

    _widget = new QWidget;
    setCentralWidget(_widget);
    const int tools_width = 256;

    _image_info = new ImageInfo(&_frame, _widget);
    connect(this, SIGNAL(new_frame()), _image_info, SLOT(update()));
    _image_info->setFixedWidth(tools_width);
    _image_info->setEnabled(false);
    
    _channel_selector = new ChannelSelector(&_frame, _widget);
    connect(this, SIGNAL(new_frame()), _channel_selector, SLOT(update()));
    _channel_selector->setFixedWidth(tools_width);

    _viewpoint_selector = new ViewpointSelector(&_frame, _widget);
    _viewpoint_selector->setFixedWidth(tools_width + tools_width / 2 + tools_width / 4);

    _interpolation_selector = new InterpolationSelector(_widget);
    _interpolation_selector->setFixedWidth(tools_width / 2);

    _channel_info = new ChannelInfo(&_frame, _channel_selector, _widget);
    _channel_info->setFixedWidth(tools_width);
    connect(this, SIGNAL(new_frame()), _channel_info, SLOT(update()));
    connect(_channel_selector, SIGNAL(channel_changed()), _channel_info, SLOT(update()));

    _range_selector = new RangeSelector(&_frame, _channel_selector, _channel_info, _widget);
    _range_selector->setFixedWidth(tools_width);
    connect(this, SIGNAL(new_frame()), _range_selector, SLOT(update()));
    connect(_channel_selector, SIGNAL(channel_changed()), _range_selector, SLOT(update_channel()));

    _gamma_selector = new GammaSelector(_channel_selector, _widget);
    _gamma_selector->setFixedWidth(tools_width);
    connect(_channel_selector, SIGNAL(channel_changed()), _gamma_selector, SLOT(update_channel()));

    _pseudocolor_selector = new PseudocolorSelector(_channel_selector, _widget);
    _pseudocolor_selector->setFixedWidth(tools_width);
    connect(_channel_selector, SIGNAL(channel_changed()), _pseudocolor_selector, SLOT(update_channel()));

    _view_area = new ViewArea(&_frame, 2 * tools_width + tools_width / 4,
	    _channel_selector,
	    _viewpoint_selector,
	    _interpolation_selector,
	    _range_selector,
	    _gamma_selector,
	    _pseudocolor_selector,
	    _widget);
    connect(this, SIGNAL(new_frame()), _view_area, SLOT(recompute()));
    connect(this, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_image_info, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_channel_selector, SIGNAL(channel_changed()), _view_area, SLOT(recompute()));
    connect(_channel_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_viewpoint_selector, SIGNAL(viewpoint_changed()), _view_area, SLOT(update()));
    connect(_viewpoint_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_interpolation_selector, SIGNAL(interpolation_changed()), _view_area, SLOT(update()));
    connect(_channel_info, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_range_selector, SIGNAL(range_changed()), _view_area, SLOT(recompute()));
    connect(_range_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_gamma_selector, SIGNAL(gamma_changed()), _view_area, SLOT(recompute()));
    connect(_pseudocolor_selector, SIGNAL(pseudocolor_changed()), _view_area, SLOT(recompute()));
    connect(_view_area, SIGNAL(update_size(int, int)), _viewpoint_selector, SLOT(update_view_area_size(int, int)));

    _pixel_info = new PixelInfo(this);
    connect(_view_area, SIGNAL(update_pixel_info(int, int, int, const float *, const float *)), 
	    _pixel_info, SLOT(update(int, int, int, const float *, const float *)));
    
    _toolbar = new QToolBar();
    _toolbar->setEnabled(false);
    _toolbar->setMovable(false);
    addToolBar(_toolbar);
    _toolbar->addWidget(_channel_selector);
    _toolbar->addSeparator();
    _toolbar->addWidget(_viewpoint_selector);
    _toolbar->addSeparator();
    _toolbar->addWidget(_interpolation_selector);

    _toolbox = new QToolBox();
    _toolbox->setMinimumWidth(tools_width);
    _toolbox->setMaximumWidth(tools_width);
    _toolbox->setEnabled(false);
    _toolbox->addItem(_channel_info, "Channel Info");
    _toolbox->addItem(_range_selector, "Range Selection");
    _toolbox->addItem(_gamma_selector, "Gamma Correction");
    _toolbox->addItem(_pseudocolor_selector, "Pseudo Color");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_image_info, 0, 0);
    layout->addWidget(_toolbox, 1, 0);
    layout->addWidget(_view_area, 0, 1, 3, 1);
    layout->addWidget(_pixel_info, 3, 0, 1, 2);
    layout->setRowStretch(2, 10000);
    layout->setColumnStretch(1, 10000);
    _widget->setLayout(layout);

    /* Create menus */

    // File menu
    QMenu *file_menu = menuBar()->addMenu(tr("&File"));
    QAction *open_image_act = new QAction(tr("&Open image..."), this);
    open_image_act->setShortcut(tr("Ctrl+O"));
    connect(open_image_act, SIGNAL(triggered()), this, SLOT(open_image()));
    file_menu->addAction(open_image_act);
    QAction *save_image_act = new QAction(tr("&Save whole image..."), this);
    save_image_act->setShortcut(tr("Ctrl+S"));
    connect(save_image_act, SIGNAL(triggered()), this, SLOT(save_image()));
    file_menu->addAction(save_image_act);
    QAction *save_view_act = new QAction(tr("Save current view..."), this);
    connect(save_view_act, SIGNAL(triggered()), this, SLOT(save_view()));
    file_menu->addAction(save_view_act);
    file_menu->addSeparator();
    QAction *quit_act = new QAction(tr("&Quit"), this);
    quit_act->setShortcut(tr("Ctrl+Q"));
    connect(quit_act, SIGNAL(triggered()), this, SLOT(close()));
    file_menu->addAction(quit_act);
    // Edit menu
    QMenu *edit_menu = menuBar()->addMenu(tr("&Edit"));
    QAction *copy_image_act = new QAction(tr("&Copy whole image"), this);
    copy_image_act->setShortcut(tr("Ctrl+C"));
    connect(copy_image_act, SIGNAL(triggered()), this, SLOT(copy_image()));
    edit_menu->addAction(copy_image_act);
    QAction *copy_view_act = new QAction(tr("Copy current view"), this);
    connect(copy_view_act, SIGNAL(triggered()), this, SLOT(copy_view()));
    edit_menu->addAction(copy_view_act);
    // Help menu
    QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
    QAction *show_aboutbox_act = new QAction(tr("&About"), this);
    show_aboutbox_act->setShortcut(tr("Ctrl+A"));
    connect(show_aboutbox_act, SIGNAL(triggered()), this, SLOT(show_aboutbox()));
    help_menu->addAction(show_aboutbox_act);
}

CVLView::~CVLView()
{
    emit make_gl_context_current();
    
    cvl_frame_t *tmp_ptr = _frame;
    _frame = NULL;
    cvl_frame_free(tmp_ptr);

    free(const_cast<char *>(_conf_file_name));
    delete _conf;
}

void CVLView::load_image(const char *filename)
{
    emit make_gl_context_current();

    _view_area->lock();
    cvl_frame_t *frame;
    cvl_load(filename, NULL, &frame);
    if (!frame)
    {
	cvl_error_set(CVL_ERROR_IO, "%s: No data.", filename);
    }
    if (cvl_error())
    {
	QMessageBox::critical(this, tr("Error"), 
		tr("<p>Cannot load image:<pre>%1</pre></p>").arg(cvl_error_msg()));
	cvl_error_reset();
	_view_area->unlock();
    }
    else
    {
	cvl_frame_free(_frame);
	_frame = frame;
	// Use floating point textures for all calculations
	cvl_frame_set_type(_frame, CVL_FLOAT);
	_image_info->setEnabled(true);
	_toolbar->setEnabled(true);
	_toolbox->setEnabled(true);
	emit new_frame();
	_view_area->unlock();
	_view_area->update();
    }
}

void CVLView::closeEvent(QCloseEvent *event)
{
    _conf->put("session-mainwindow-x", pos().x());
    _conf->put("session-mainwindow-y", pos().y());
    _conf->put("session-mainwindow-width", size().width());
    _conf->put("session-mainwindow-height", size().height());
    _conf->put("session-mainwindow-maximized", isMaximized());
    _conf->put("session-last-open-dir", qPrintable(_last_open_dir.absolutePath()));
    _conf->put("session-last-save-dir", qPrintable(_last_save_dir.absolutePath()));
    _conf->remove_cruft();
    try
    {
	_conf->save(_conf_file_name);
    }
    catch (err e) {}
    event->accept();
}

void CVLView::open_image()
{
    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Open image"));
    file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
    file_dialog->setDirectory(_last_open_dir);
    QStringList filters;
    filters << tr("Portable Floating-point Streams (*.pfs)") 
	<< tr("NetPBM files (*.pnm *.pbm *.pgm *.ppm *.pam)")
	<< tr("All files (*)");
    file_dialog->setFilters(filters);
    file_dialog->setFileMode(QFileDialog::ExistingFile);
    if (!file_dialog->exec())
	return;
    QString file_name = file_dialog->selectedFiles().at(0);
    if (file_name.isEmpty())
	return;
    _last_open_dir = file_dialog->directory();
    load_image(qPrintable(file_name));
}

void CVLView::save(bool whole_image)
{
    if (!_frame)
    {
	QMessageBox::critical(this, tr("Error"), tr("No data loaded yet."));
	return;
    }

    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Save image"));
    file_dialog->setDefaultSuffix("png");
    file_dialog->setAcceptMode(QFileDialog::AcceptSave);
    file_dialog->setDirectory(_last_save_dir);
    QStringList filters;
    filters << tr("PNG image files (*.png)") << tr("JPEG image files (*.jpg") << tr("All files (*)");
    file_dialog->setFilters(filters);
    file_dialog->setFileMode(QFileDialog::AnyFile);
    if (!file_dialog->exec())
	return;
    QString file_name = file_dialog->selectedFiles().at(0);
    if (file_name.isEmpty())
	return;
    QImage img = (whole_image ? _view_area->get_image() : _view_area->get_view());
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool success = img.save(file_name, file_name.endsWith(".jpg", Qt::CaseInsensitive) ? "jpg" : "png");
    QApplication::restoreOverrideCursor();
    if (!success)
	QMessageBox::critical(this, tr("Error"), QString(tr("Saving %1 failed.")).arg(file_name));

    _last_save_dir = file_dialog->directory();
}

void CVLView::save_image()
{
    save(true);
}

void CVLView::save_view()
{
    save(false);
}

void CVLView::copy(bool whole_image)
{
    if (!_frame)
    {
	QMessageBox::critical(this, tr("Error"), tr("No data loaded yet."));
	return;
    }

    QApplication::clipboard()->setImage(whole_image ? _view_area->get_image() : _view_area->get_view());
}

void CVLView::copy_image()
{
    copy(true);
}

void CVLView::copy_view()
{
    copy(false);
}

void CVLView::show_aboutbox()
{
    QMessageBox::about(this, tr("About " PACKAGE_NAME), tr(
		"<p>%1 version %2</p>"
		"<p>Copyright (C) 2007  Martin Lambers and others.<br>"
		"This is free software. You may redistribute copies of it under the terms of "
		"the <a href=\"http://www.gnu.org/licenses/old-licenses/gpl-2.0.html\">GNU General Public License</a>.<br>"
		"There is NO WARRANTY, to the extent permitted by law.<br>"
		"See the <a href=\"http://cvtool.sourceforge.net/\">cvtool homepage</a> "
		"for more information on this software.</p>").arg(PACKAGE_NAME).arg(VERSION));
}