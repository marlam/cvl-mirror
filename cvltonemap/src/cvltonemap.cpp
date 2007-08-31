/*
 * cvltonemap.cpp
 *
 * This file is part of cvltonemap, a tone mapping tool using the CVL library.
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
#include <QGroupBox>
#include <QIcon>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>

#include "err.h"
#include "conf.h"

#include "tonemap_selector.h"
#include "postproc_selector.h"
#include "viewpoint_selector.h"
#include "view_area.h"
#include "cvltonemap.h"


CVLToneMap::CVLToneMap()
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
    const int tools_width = 256 + 16;

    _viewpoint_selector = new ViewpointSelector(&_frame, _widget);
    _viewpoint_selector->setFixedWidth(tools_width + tools_width / 2 + tools_width / 4);

    _tonemap_box = new QGroupBox("Tone Mapping");
    _tonemap_box->setFixedWidth(tools_width);
    _tonemap_box->setEnabled(false);
    _tonemap_selector = new TonemapSelector(&_frame, this);
    QGridLayout *tonemap_layout = new QGridLayout;
    tonemap_layout->addWidget(_tonemap_selector, 0, 0);
    _tonemap_box->setLayout(tonemap_layout);
    connect(this, SIGNAL(new_image()), _tonemap_selector, SLOT(update()));
    
    _postproc_box = new QGroupBox("Postprocessing");
    _postproc_box->setFixedWidth(tools_width);
    _postproc_box->setEnabled(false);
    _postproc_selector = new PostprocSelector(this);
    QGridLayout *postproc_layout = new QGridLayout;
    postproc_layout->addWidget(_postproc_selector, 0, 0);
    _postproc_box->setLayout(postproc_layout);

    _view_area = new ViewArea(&_frame,
	    _viewpoint_selector,
	    _tonemap_selector,
	    _postproc_selector,
	    2 * tools_width + tools_width / 4, _widget);
    connect(this, SIGNAL(new_image()), _view_area, SLOT(recompute()));
    connect(this, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_tonemap_selector, SIGNAL(tonemap_changed()), _view_area, SLOT(recompute()));
    connect(_tonemap_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_postproc_selector, SIGNAL(postproc_changed()), _view_area, SLOT(recompute()));
    connect(_viewpoint_selector, SIGNAL(viewpoint_changed()), _view_area, SLOT(update()));
    connect(_viewpoint_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_view_area, SIGNAL(update_size(int, int)), _viewpoint_selector, SLOT(update_view_area_size(int, int)));
    
    _toolbar = new QToolBar();
    _toolbar->setEnabled(false);
    _toolbar->setMovable(false);
    addToolBar(_toolbar);
    _toolbar->addWidget(_viewpoint_selector);
    
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_tonemap_box, 0, 0);
    layout->addWidget(_postproc_box, 1, 0);
    layout->addWidget(_view_area, 0, 1, 3, 1);
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
    QAction *save_image_act = new QAction(tr("&Save image..."), this);
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
    QAction *copy_image_act = new QAction(tr("&Copy image"), this);
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

CVLToneMap::~CVLToneMap()
{
    emit make_gl_context_current();
    
    cvl_frame_t *tmp_ptr = _frame;
    _frame = NULL;
    cvl_frame_free(tmp_ptr);

    free(const_cast<char *>(_conf_file_name));
    delete _conf;
}

void CVLToneMap::load_image(const char *filename)
{
    emit make_gl_context_current();

    _view_area->lock();
    cvl_frame_t *frame;
    cvl_load_pfs(filename, &frame);
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
	return;
    }
    else
    {
	// Make sure that the image is in CVL_XYZ format.
	if (cvl_frame_format(frame) == CVL_UNKNOWN)
	{
	    int channel_x = -1;
	    int channel_y = -1;
	    int channel_z = -1;
	    for (int c = 0; c < cvl_frame_channels(frame); c++)
	    {
		if (strcmp(cvl_frame_channel_name(frame, c), "X") == 0)
		    channel_x = c;
		else if (strcmp(cvl_frame_channel_name(frame, c), "Y") == 0)
		    channel_y = c;
		else if (strcmp(cvl_frame_channel_name(frame, c), "Z") == 0)
		    channel_z = c;
	    }
	    if (channel_x >= 0 && channel_y >= 0 && channel_z >= 0)
	    {
		cvl_frame_t *X = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
			1, CVL_LUM, CVL_FLOAT, CVL_TEXTURE);
		cvl_frame_t *Y = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
			1, CVL_LUM, CVL_FLOAT, CVL_TEXTURE);
		cvl_frame_t *Z = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
			1, CVL_LUM, CVL_FLOAT, CVL_TEXTURE);
		cvl_channel_extract(X, frame, channel_x);
		cvl_channel_extract(Y, frame, channel_y);
		cvl_channel_extract(Z, frame, channel_z);
		cvl_frame_set_format(frame, CVL_XYZ);
		cvl_channel_combine(frame, X, Y, Z, NULL);
		cvl_frame_free(X);
		cvl_frame_free(Y);
		cvl_frame_free(Z);
	    }
	    else if (channel_y >= 0)
	    {
		cvl_frame_t *Y = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
			1, CVL_LUM, CVL_FLOAT, CVL_TEXTURE);
		cvl_channel_extract(Y, frame, channel_y);
		cvl_frame_free(frame);
		frame = Y;
	    }
	    else
	    {
		QMessageBox::critical(this, tr("Error"), tr("Input data is not an image."));
		_view_area->unlock();
		return;
	    }
	}
	cvl_convert_format_inplace(frame, CVL_XYZ);
	// Make sure that the Y range is [0,1]. Keep info about absolute
	// luminances in a tag.
	float max_luminance;
	const char *luminance_tag;
	cvl_reduce(frame, CVL_REDUCE_MAX, 1, &max_luminance);
	luminance_tag = cvl_taglist_get(cvl_frame_taglist(frame), "LUMINANCE");
	bool have_absolute_luminance = (max_luminance > 1.001f 
		|| (luminance_tag && strcmp(luminance_tag, "ABSOLUTE") == 0));
	if (have_absolute_luminance)
	{
	    cvl_frame_t *tmpframe = cvl_frame_new_tpl(frame);
	    cvl_luminance_range(tmpframe, frame, 0.0f, max_luminance);
	    cvl_frame_free(frame);
	    frame = tmpframe;
	    cvl_taglist_put(cvl_frame_taglist(frame), 
		    "X-MAX-LUMINANCE", mh_string("%.8f", max_luminance).c_str());
	}
	else
	{
	    cvl_taglist_put(cvl_frame_taglist(frame), "X-MAX-LUMINANCE", "UNKNOWN");
	}
	// Now replace the old frame, if any.
	cvl_frame_free(_frame);
	_frame = frame;
	_toolbar->setEnabled(true);
	_tonemap_box->setEnabled(true);
	_postproc_box->setEnabled(true);
	emit new_image();
	_view_area->unlock();
	_view_area->update();
    }
}

void CVLToneMap::closeEvent(QCloseEvent *event)
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

void CVLToneMap::open_image()
{
    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Open image"));
    file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
    file_dialog->setDirectory(_last_open_dir);
    QStringList filters;
    filters << tr("Portable Floating-point Streams (*.pfs)") 
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

void CVLToneMap::save(bool whole_image)
{
    if (!_frame)
    {
	QMessageBox::critical(this, tr("Error"), tr("No image loaded yet."));
	return;
    }

    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Save image"));
    file_dialog->setDefaultSuffix("jpg");
    file_dialog->setAcceptMode(QFileDialog::AcceptSave);
    file_dialog->setDirectory(_last_save_dir);
    QStringList filters;
    filters << tr("JPEG image files (*.jpg)") << tr("PNG image files (*.png)") << tr("All files (*)");
    file_dialog->setFilters(filters);
    file_dialog->setFileMode(QFileDialog::AnyFile);
    if (!file_dialog->exec())
	return;
    QString file_name = file_dialog->selectedFiles().at(0);
    if (file_name.isEmpty())
	return;
    QImage img = (whole_image ? _view_area->get_image() : _view_area->get_view());
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool success = img.save(file_name, file_name.endsWith(".png", Qt::CaseInsensitive) ? "png" : "jpg");
    QApplication::restoreOverrideCursor();
    if (!success)
	QMessageBox::critical(this, tr("Error"), QString(tr("Saving %1 failed.")).arg(file_name));

    _last_save_dir = file_dialog->directory();
}

void CVLToneMap::save_image()
{
    save(true);
}

void CVLToneMap::save_view()
{
    save(false);
}

void CVLToneMap::copy(bool whole_image)
{
    if (!_frame)
    {
	QMessageBox::critical(this, tr("Error"), tr("No image loaded yet."));
	return;
    }

    QApplication::clipboard()->setImage(whole_image ? _view_area->get_image() : _view_area->get_view());
}

void CVLToneMap::copy_image()
{
    copy(true);
}

void CVLToneMap::copy_view()
{
    copy(false);
}

void CVLToneMap::show_aboutbox()
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