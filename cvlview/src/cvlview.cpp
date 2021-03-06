/*
 * cvlview.cpp
 *
 * This file is part of cvlview, an image viewer using the CVL library.
 *
 * Copyright (C) 2007, 2008, 2009, 2010  Martin Lambers <marlam@marlam.de>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
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
#include <cerrno>
#include <cstring>

#define GLEW_STATIC 1
#include <GL/glew.h>

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
#include <QMenuBar>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QStatusBar>
#include <QSpinBox>
#include <QProgressBar>
#include <QProgressDialog>

#include "glvm.h"
using namespace glvm;

#include "err.h"
#include "conf.h"
#include "datafile.h"

#include "dataset_selector.h"
#include "channel_selector.h"
#include "scale_selector.h"
#include "translation_selector.h"
#include "rotation_selector.h"
#include "interpolation_selector.h"
#include "color_selector.h"
#include "grid_selector.h"
#include "frame_info.h"
#include "channel_info.h"
#include "range_selector.h"
#include "gamma_selector.h"
#include "pseudocolor_selector.h"
#include "heightmap_selector.h"
#include "view_area.h"
#include "pixel_info.h"
#include "cvlview.h"


CVLView::CVLView()
{
    setWindowTitle(PACKAGE_NAME);
    setWindowIcon(QIcon(":icons/appicon.png"));
    _conf_file_name = mh_get_apprcpath(PACKAGE_NAME);
    _conf = new Conf();
    try
    {
	_conf->load(_conf_file_name);
    }
    catch (err e) {}
    _last_open_dir = QDir(_conf->get("session-last-open-dir", qPrintable(QDir::homePath())));
    _last_save_dir = QDir(_conf->get("session-last-save-dir", qPrintable(QDir::homePath())));
    _datafile = NULL;
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
    const int tools_width = 280;
    
    _dataset_selector = new DatasetSelector(&_datafile, _widget);
    connect(_dataset_selector, SIGNAL(dataset_changed()), this, SLOT(open_frame()));
    connect(this, SIGNAL(new_datafile()), _dataset_selector, SLOT(reset()));
    
    _channel_selector = new ChannelSelector(&_frame, _widget);
    connect(this, SIGNAL(new_frame()), _channel_selector, SLOT(update()));
    connect(this, SIGNAL(new_datafile()), _channel_selector, SLOT(reset()));

    _scale_selector = new ScaleSelector(&_frame, _widget);
    connect(this, SIGNAL(new_datafile()), _scale_selector, SLOT(reset()));

    _translation_selector = new TranslationSelector(_widget);
    connect(this, SIGNAL(new_datafile()), _translation_selector, SLOT(reset()));

    _rotation_selector = new RotationSelector(_widget);
    connect(this, SIGNAL(new_datafile()), _rotation_selector, SLOT(reset()));

    _interpolation_selector = new InterpolationSelector(_widget);
    connect(this, SIGNAL(new_datafile()), _interpolation_selector, SLOT(reset()));

    _color_selector = new ColorSelector(0.3f, 0.3f, 0.3f, _widget);
    connect(this, SIGNAL(new_datafile()), _color_selector, SLOT(reset()));

    _grid_selector = new GridSelector(1.0f, 1.0f, 1.0f, _widget);
    connect(this, SIGNAL(new_datafile()), _grid_selector, SLOT(reset()));

    _frame_info = new FrameInfo(&_datafile, &_frame, _widget);
    connect(this, SIGNAL(new_frame()), _frame_info, SLOT(update()));
    _frame_info->setFixedWidth(tools_width);
    _frame_info->setEnabled(false);

    _channel_info = new ChannelInfo(&_frame, _channel_selector, _widget);
    connect(this, SIGNAL(new_frame()), _channel_info, SLOT(update()));
    connect(this, SIGNAL(new_datafile()), _channel_info, SLOT(reset()));
    connect(_channel_selector, SIGNAL(channel_changed()), _channel_info, SLOT(update()));
    _channel_info->setFixedWidth(tools_width);

    _range_selector = new RangeSelector(&_frame, _channel_selector, _channel_info, _widget);
    connect(this, SIGNAL(new_frame()), _range_selector, SLOT(update()));
    connect(this, SIGNAL(new_datafile()), _range_selector, SLOT(reset()));
    connect(_channel_selector, SIGNAL(channel_changed()), _range_selector, SLOT(update_channel()));
    _range_selector->setFixedWidth(tools_width);

    _gamma_selector = new GammaSelector(_channel_selector, _widget);
    connect(_channel_selector, SIGNAL(channel_changed()), _gamma_selector, SLOT(update_channel()));
    connect(this, SIGNAL(new_datafile()), _gamma_selector, SLOT(reset()));
    _gamma_selector->setFixedWidth(tools_width);

    _pseudocolor_selector = new PseudocolorSelector(_channel_selector, _widget);
    connect(_channel_selector, SIGNAL(channel_changed()), _pseudocolor_selector, SLOT(update_channel()));
    connect(this, SIGNAL(new_datafile()), _pseudocolor_selector, SLOT(reset()));
    _pseudocolor_selector->setFixedWidth(tools_width);

    _heightmap_selector = new HeightmapSelector(&_frame, _widget);
    connect(this, SIGNAL(new_frame()), _heightmap_selector, SLOT(update()));
    connect(this, SIGNAL(new_datafile()), _heightmap_selector, SLOT(reset()));
    _heightmap_selector->setFixedWidth(tools_width);

    _view_area = new ViewArea(&_frame, 2 * tools_width + tools_width / 4,
	    _channel_info,
	    _channel_selector,
	    _scale_selector,
	    _translation_selector,
	    _rotation_selector,
	    _interpolation_selector,
	    _color_selector,
	    _grid_selector,
	    _range_selector,
	    _gamma_selector,
	    _pseudocolor_selector,
	    _heightmap_selector,
	    _widget);
    connect(this, SIGNAL(new_frame()), _view_area, SLOT(recompute()));
    connect(this, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_dataset_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_frame_info, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_channel_selector, SIGNAL(channel_changed()), _view_area, SLOT(recompute()));
    connect(_channel_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_scale_selector, SIGNAL(view_changed()), _view_area, SLOT(update()));
    connect(_scale_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_translation_selector, SIGNAL(view_changed()), _view_area, SLOT(update()));
    connect(_rotation_selector, SIGNAL(rotation_changed()), _view_area, SLOT(rotation_changed()));
    connect(_interpolation_selector, SIGNAL(interpolation_changed()), _view_area, SLOT(update()));
    connect(_color_selector, SIGNAL(color_changed()), _view_area, SLOT(update()));
    connect(_grid_selector, SIGNAL(grid_changed()), _view_area, SLOT(update()));
    connect(_channel_info, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_range_selector, SIGNAL(range_changed()), _view_area, SLOT(recompute()));
    connect(_range_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_gamma_selector, SIGNAL(gamma_changed()), _view_area, SLOT(recompute()));
    connect(_pseudocolor_selector, SIGNAL(pseudocolor_changed()), _view_area, SLOT(recompute()));
    connect(_heightmap_selector, SIGNAL(heightmap_changed()), _view_area, SLOT(update()));
    connect(_heightmap_selector, SIGNAL(make_gl_context_current()), _view_area, SLOT(make_gl_context_current()));
    connect(_view_area, SIGNAL(update_size(int, int)), _scale_selector, SLOT(update_view_area_size(int, int)));
    connect(_view_area, SIGNAL(update_rotation(const quat &)), _rotation_selector, SLOT(update_rotation(const quat &)));

    _pixel_info = new PixelInfo(this);
    connect(_view_area, SIGNAL(update_pixel_info(int, int, int, const float *, const float *)), 
	    _pixel_info, SLOT(update(int, int, int, const float *, const float *)));
    
    _toolbar1 = new QToolBar();
    _toolbar1->setEnabled(false);
    _toolbar1->setMovable(false);
    addToolBar(_toolbar1);
    addToolBarBreak();
    _toolbar1->addWidget(_dataset_selector);
    _toolbar1->addSeparator();
    _toolbar1->addWidget(_channel_selector);
    _toolbar1->addSeparator();
    _toolbar1->addWidget(_interpolation_selector);
    _toolbar1->addSeparator();
    _toolbar1->addWidget(_color_selector);
    _toolbar1->addSeparator();
    _toolbar1->addWidget(_grid_selector);

    _toolbar2 = new QToolBar();
    _toolbar2->setEnabled(false);
    _toolbar2->setMovable(false);
    addToolBar(_toolbar2);
    _toolbar2->addWidget(_scale_selector);
    _toolbar2->addSeparator();
    _toolbar2->addWidget(_translation_selector);
    _toolbar2->addSeparator();
    _toolbar2->addWidget(_rotation_selector);

    _toolbox = new QToolBox();
    _toolbox->setMinimumWidth(tools_width);
    _toolbox->setMaximumWidth(tools_width);
    _toolbox->setEnabled(false);
    _toolbox->addItem(_channel_info, "Channel Info");
    _toolbox->addItem(_range_selector, "Range Selection");
    _toolbox->addItem(_gamma_selector, "Gamma Correction");
    _toolbox->addItem(_pseudocolor_selector, "Pseudo Color");
    _toolbox->addItem(_heightmap_selector, "3D View");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(_frame_info, 0, 0);
    layout->addWidget(_toolbox, 1, 0);
    layout->addWidget(_view_area, 0, 1, 3, 1);
    layout->addWidget(_pixel_info, 3, 0, 1, 2);
    layout->setRowStretch(2, 10000);
    layout->setColumnStretch(1, 10000);
    _widget->setLayout(layout);

    /* Create menus */

    // File menu
    QMenu *file_menu = menuBar()->addMenu(tr("&File"));
    QAction *open_datafile_act = new QAction(tr("&Open data file..."), this);
    open_datafile_act->setShortcut(tr("Ctrl+O"));
    connect(open_datafile_act, SIGNAL(triggered()), this, SLOT(open_datafile()));
    file_menu->addAction(open_datafile_act);
    file_menu->addSeparator();
    QAction *save_view_act = new QAction(tr("&Save current view..."), this);
    save_view_act->setShortcut(tr("Ctrl+S"));
    connect(save_view_act, SIGNAL(triggered()), this, SLOT(save_view()));
    file_menu->addAction(save_view_act);
    QAction *save_image_act = new QAction(tr("Save 1:1 2D view..."), this);
    connect(save_image_act, SIGNAL(triggered()), this, SLOT(save_image()));
    file_menu->addAction(save_image_act);
    file_menu->addSeparator();
    QAction *save_video_act = new QAction(tr("Save video..."), this);
    connect(save_video_act, SIGNAL(triggered()), this, SLOT(save_video()));
    file_menu->addAction(save_video_act);
    file_menu->addSeparator();
    QAction *quit_act = new QAction(tr("&Quit"), this);
    quit_act->setShortcut(tr("Ctrl+Q"));
    connect(quit_act, SIGNAL(triggered()), this, SLOT(close()));
    file_menu->addAction(quit_act);
    // Edit menu
    QMenu *edit_menu = menuBar()->addMenu(tr("&Edit"));
    QAction *copy_view_act = new QAction(tr("&Copy current view"), this);
    copy_view_act->setShortcut(tr("Ctrl+C"));
    connect(copy_view_act, SIGNAL(triggered()), this, SLOT(copy_view()));
    edit_menu->addAction(copy_view_act);
    QAction *copy_image_act = new QAction(tr("Copy 1:1 2D view"), this);
    connect(copy_image_act, SIGNAL(triggered()), this, SLOT(copy_image()));
    edit_menu->addAction(copy_image_act);
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

void CVLView::activate_frame(cvl_frame_t *frame)
{
    emit make_gl_context_current();
    _view_area->lock();
    cvl_frame_free(_frame);
    _frame = frame;
    // Use floating point textures for all calculations
    cvl_frame_set_type(_frame, CVL_FLOAT);
    emit new_frame();
    _view_area->unlock();
    _view_area->update();
}

void CVLView::load_datafile(const char *filename)
{
    emit make_gl_context_current();
    
    DataFile *datafile;
    cvl_frame_t *frame;
    try
    {
	datafile = new DataFile(filename);
	frame = datafile->read();
    }
    catch (err e) 
    {
	QMessageBox::critical(this, tr("Error"), e.msg().c_str());
	return;    
    }
    cvl_error_reset();
    if (_datafile)
    {
	delete _datafile;
    }
    _datafile = datafile;
    setWindowTitle(mh_string("%s.%s (%s)",
		qPrintable(QFileInfo(filename).baseName()),
		qPrintable(QFileInfo(filename).completeSuffix()), 
		PACKAGE_NAME).c_str());
    
    // With Qt 4.2, it was sufficient to just enable a toolbar; all its
    // widgets were then enabled automatically. This does not seem to work
    // with Qt 4.4 anymore, so we enable all toolbar widgets manually here.
    _toolbar1->setEnabled(true);
    _dataset_selector->setEnabled(true);
    _channel_selector->setEnabled(true);
    _interpolation_selector->setEnabled(true);
    _color_selector->setEnabled(true);
    _grid_selector->setEnabled(true);    
    _toolbar2->setEnabled(true);
    _scale_selector->setEnabled(true);
    _translation_selector->setEnabled(true);
    _rotation_selector->setEnabled(true);
    _frame_info->setEnabled(true);
    _toolbox->setEnabled(true);
    
    _view_area->lock();
    emit new_datafile();
    _view_area->unlock();
    _view_area->update();
    activate_frame(frame);
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

void CVLView::open_datafile()
{
    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Open image"));
    file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
    file_dialog->setDirectory(_last_open_dir);
    QStringList filters;
    filters << tr("All supported files (*.pfs *.pnm *.pbm *.pgm *.ppm *.pam)")
	<< tr("Portable Floating-point Streams (*.pfs)") 
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
    load_datafile(qPrintable(file_name));
}

void CVLView::open_frame()
{
    emit make_gl_context_current();
    cvl_frame_t *frame;
    try
    {
	frame = _datafile->read();
    }
    catch (err e)
    {
	QMessageBox::critical(this, tr("Error"), e.msg().c_str());
	_view_area->unlock();
	return;    
    }
    cvl_error_reset();
    if (frame)
    {
	activate_frame(frame);
    }
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

void CVLView::save_video()
{
    if (!_frame)
    {
	QMessageBox::critical(this, tr("Error"), tr("No data loaded yet."));
	return;
    }

    // Get dataset selection
    int dataset_start = _dataset_selector->get_current();
    int dataset_end = _dataset_selector->get_max() > 0 ? _dataset_selector->get_max() : 9999;
    int dataset_step = 1;
    QDialog *dataset_dialog = new QDialog(this);
    dataset_dialog->setModal(true);
    dataset_dialog->setWindowTitle("Select data sets");
    QGridLayout *dd_layout = new QGridLayout;
    QLabel *start_label = new QLabel("Start:");
    dd_layout->addWidget(start_label, 0, 0);
    QSpinBox *start_spinbox = new QSpinBox();
    start_spinbox->setRange(1, dataset_end);
    start_spinbox->setValue(dataset_start);
    dd_layout->addWidget(start_spinbox, 0, 1);
    QLabel *end_label = new QLabel("End:");
    dd_layout->addWidget(end_label, 1, 0);
    QSpinBox *end_spinbox = new QSpinBox();
    end_spinbox->setRange(1, dataset_end);
    end_spinbox->setValue(dataset_end);
    dd_layout->addWidget(end_spinbox, 1, 1);
    QLabel *step_label = new QLabel("Step:");
    dd_layout->addWidget(step_label, 2, 0);
    QSpinBox *step_spinbox = new QSpinBox();
    step_spinbox->setRange(1, 999);
    step_spinbox->setValue(1);
    dd_layout->addWidget(step_spinbox, 2, 1);
    QPushButton *dd_ok_btn = new QPushButton(tr("&OK"), dataset_dialog);
    dd_ok_btn->setDefault(true);
    connect(dd_ok_btn, SIGNAL(clicked()), dataset_dialog, SLOT(accept()));
    dd_layout->addWidget(dd_ok_btn, 3, 0);
    QPushButton *dd_cancel_btn = new QPushButton(tr("&Cancel"), dataset_dialog);
    connect(dd_cancel_btn, SIGNAL(clicked()), dataset_dialog, SLOT(reject()));
    dd_layout->addWidget(dd_cancel_btn, 3, 1);
    dataset_dialog->setLayout(dd_layout);
    if (dataset_dialog->exec() == QDialog::Rejected)
   	return;
    dataset_start = start_spinbox->value();
    dataset_end = end_spinbox->value();
    dataset_step = step_spinbox->value();

    // Get video file name
    QFileDialog *file_dialog = new QFileDialog(this);
    file_dialog->setWindowTitle(tr("Save image"));
    file_dialog->setDefaultSuffix("ppm");
    file_dialog->setAcceptMode(QFileDialog::AcceptSave);
    file_dialog->setDirectory(_last_save_dir);
    QStringList filters;
    filters << tr("NetPBM color files (*.ppm)") << tr("All files (*)");
    file_dialog->setFilters(filters);
    file_dialog->setFileMode(QFileDialog::AnyFile);
    if (!file_dialog->exec())
	return;
    QString file_name = file_dialog->selectedFiles().at(0);
    if (file_name.isEmpty())
	return;

    // Open file
    FILE *file = fopen(qPrintable(file_name), "w");
    if (!file)
    {
	QMessageBox::critical(this, tr("Error"), 
		QString(mh_string("Saving %s failed: %s", qPrintable(file_name), strerror(errno)).c_str()));
	return;
    }
    
    // Do it
    QProgressDialog *progress_dialog = new QProgressDialog("Saving video...", "Cancel", dataset_start - 1, dataset_end, this);
    progress_dialog->setWindowModality(Qt::WindowModal);
    progress_dialog->setMinimumDuration(0);
    progress_dialog->setValue(dataset_start - 1);
    int dataset_bak = _dataset_selector->get_current();
    for (int d = dataset_start; d <= dataset_end; d += dataset_step)
    {
	progress_dialog->setValue(d);
	QCoreApplication::processEvents();
	_dataset_selector->set_current(d);
	QCoreApplication::processEvents();
    	QImage img = _view_area->get_view();
	QCoreApplication::processEvents();
	emit make_gl_context_current();
	cvl_frame_t *frame = cvl_frame_new(img.width(), img.height(), 3, CVL_RGB, CVL_UINT8, CVL_MEM);
	uint8_t *p = static_cast<uint8_t *>(cvl_frame_pointer(frame));
	QCoreApplication::processEvents();
	for (int y = 0; y < cvl_frame_height(frame); y++)
	{
	    for (int x = 0; x < cvl_frame_width(frame); x++)
	    {
		QRgb pixel = img.pixel(x, y);
		p[3 * (y * cvl_frame_width(frame) + x) + 0] = qRed(pixel);
		p[3 * (y * cvl_frame_width(frame) + x) + 1] = qGreen(pixel);
		p[3 * (y * cvl_frame_width(frame) + x) + 2] = qBlue(pixel);
	    }
	}
	QCoreApplication::processEvents();
	cvl_write_pnm(file, frame);
	cvl_frame_free(frame);
	if (progress_dialog->wasCanceled())
	{
	    break;
	}
    }
    delete progress_dialog;
    if (cvl_error())
    {
	QMessageBox::critical(this, tr("Error"), 
		QString(mh_string("Saving %s failed: %s", qPrintable(file_name), cvl_error_msg()).c_str()));
	cvl_error_reset();
	return;
    }
    if (fclose(file) != 0)
    {
	QMessageBox::critical(this, tr("Error"), 
		QString(mh_string("Saving %s failed: %s", qPrintable(file_name), strerror(errno)).c_str()));
	return;
    }
    _dataset_selector->set_current(dataset_bak);
    _last_save_dir = file_dialog->directory();
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
		"<p>This is %1 version %2, using CVL version %3.</p>"
		"<p>Copyright (C) 2010  Martin Lambers and others.<br>"
		"This is free software. You may redistribute copies of it under the terms of "
		"the <a href=\"http://www.gnu.org/licenses/gpl.html\">"
		"GNU General Public License</a>.<br>"
		"There is NO WARRANTY, to the extent permitted by law.</p>"
		"See <a href=\"https://marlam.de/cvl\">"
		"https://marlam.de/cvl</a> "
		"for more information on this software.</p>")
	    .arg(PACKAGE_NAME).arg(VERSION).arg(cvl_version(NULL, NULL, NULL)));
}
