/*
 * dataset_selector.h
 *
 * This file is part of cvlview, an image viewer using the CVL library.
 *
 * Copyright (C) 2007, 2008, 2009, 2010
 * Martin Lambers <marlam@marlam.de>
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

#ifndef DATASET_SELECTOR_H
#define DATASET_SELECTOR_H

#include "config.h"

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "datafile.h"


class DatasetSelector : public QWidget
{
    Q_OBJECT
	
    private:
	DataFile **_datafile;
	QSpinBox *_nr_spinbox;
	QPushButton *_scan_button;
        QPushButton *_reload_button;
	QLabel *_total_label;
	bool _total_label_was_set;
	bool _lock;

    private slots:
	void set_nr(int nr);
        void scan_button_clicked();
        void reload_button_clicked();

    public:
	DatasetSelector(DataFile **datafile, QWidget *parent = NULL);	
	~DatasetSelector();

	int get_current()
	{
	    return _nr_spinbox->value();
	}

	int get_max()
	{
	    return (*_datafile) ? (*_datafile)->total() - 1 : -1;
	}

	void set_current(int d)
	{
	    _nr_spinbox->setValue(d);
	}

    public slots:
	void reset();
    
    signals:
	void make_gl_context_current();
	void dataset_changed();
};

#endif
