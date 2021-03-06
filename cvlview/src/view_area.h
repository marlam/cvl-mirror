/*
 * view_area.h
 *
 * This file is part of cvlview, an image viewer using the CVL library.
 *
 * Copyright (C) 2007, 2008, 2009  Martin Lambers <marlam@marlam.de>
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

#ifndef VIEW_AREA_H
#define VIEW_AREA_H

#include "config.h"

#define GLEW_STATIC 1
#include <GL/glew.h>

#include <QGLWidget>
#include <QImage>
#include <QMouseEvent>
#include <QWheelEvent>

#include <cvl/cvl.h>

#include "glvm.h"
#include "arcball.h"

#include "channel_info.h"
#include "channel_selector.h"
#include "scale_selector.h"
#include "translation_selector.h"
#include "rotation_selector.h"
#include "interpolation_selector.h"
#include "color_selector.h"
#include "grid_selector.h"
#include "range_selector.h"
#include "gamma_selector.h"
#include "pseudocolor_selector.h"
#include "heightmap_selector.h"


class ViewArea : public QGLWidget
{
    Q_OBJECT

    private:
	// Image
	cvl_frame_t **_frame;
	// Size of the view area
	int _width, _height;
	// Lock
	bool _lock;
	// Selector widgets to get parameters from
	ChannelInfo *_channel_info;
	ChannelSelector *_channel_selector;
	ScaleSelector *_scale_selector;
	TranslationSelector *_translation_selector;
	RotationSelector *_rotation_selector;
	InterpolationSelector *_interpolation_selector;
	ColorSelector *_color_selector;
	GridSelector *_grid_selector;
	RangeSelector *_range_selector;
	GammaSelector *_gamma_selector;
	PseudocolorSelector *_pseudocolor_selector;
	HeightmapSelector *_heightmap_selector;
	// Last processing parameters
	cvl_frame_t *_processed_frame;
	// Image to be rendered
	cvl_frame_t *_render_frame;
	// Recompute _render_frame?
	bool _recompute;
	// Processing buffers
	cvl_frame_t *_frame1, *_frame2;
	// 2D or 3D view?
	bool _flat_view;
	// Program for heightmap rendering
	GLuint _heightmap_quads_prg;
	GLuint _heightmap_strip_prg;
	// Data buffers for heightmap rendering
	GLuint _heightmap_texcoord0_buffer;
	GLuint _heightmap_texcoord1_buffer;
	GLuint _heightmap_vertex_buffer;
	int _heightmap_buffers_mode;
	bool _heightmap_buffers_are_current;
	// Used area of the framebuffer
	int _fb_x, _fb_y, _fb_w, _fb_h;
	// Mouse position
	QPoint _mouse_pos;
	// Pixel info
	float _pixel_val[4];
	float _pixel_lum;
	// Dragging and rotating
	bool _dragging;
	QPoint _drag_startpoint;
	bool _rotating;
	ArcBall *_arcball;
	glvm::quat _rotation;
	// Error handling
	bool _cvl_init_failed;
	bool _rendering_fails;

	void cvl_error_msgbox();
	void pixel_info();

	float rgb_to_lum(float r, float g, float b);
	float hsl_to_lum_helper(float tmp2, float tmp1, float H);
	float hsl_to_lum(float h, float s, float l);

    public slots:
	void make_gl_context_current();
        void recompute();
        void update();
	void rotation_changed();

    public:
	ViewArea(cvl_frame_t **frame, 
		int min_size,
		ChannelInfo *channel_info,
		ChannelSelector *channel_selector,
		ScaleSelector *scale_selector,
		TranslationSelector *translation_selector,
		RotationSelector *rotation_selector,
		InterpolationSelector *interpolation_selector,
		ColorSelector *color_selector,
		GridSelector *grid_selector,
		RangeSelector *range_selector,
		GammaSelector *gamma_selector,
		PseudocolorSelector *pseudocolor_selector,
		HeightmapSelector *heightmap_selector,
		QWidget *parent = NULL);
	~ViewArea();

	void lock()
	{
	    _lock = true;
	}

	void unlock()
	{
	    _lock = false;
	}

	QImage get_image();
	QImage get_view();

	virtual void mousePressEvent(QMouseEvent *event);
    	virtual void mouseReleaseEvent(QMouseEvent *event);
   	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

    signals:
	void update_pixel_info(int x, int y, int channels, const float *val, const float *lum);
	void update_size(int w, int h);
	void update_rotation(const quat &rot);

    protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
};

#endif
