/*
 * cvl_field.h
 * 
 * This file is part of CVL, a computer vision library.
 *
 * Copyright (C) 2005, 2006  Martin Lambers <marlam@marlam.de>
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
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef CVL_FIELD_H
#define CVL_FIELD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cvl_assert.h"
#include "cvl_math.h"

typedef struct
{
    size_t _element_size;
    int _width;
    int _height;
    void *_p;
} cvl_field_t;

cvl_field_t *cvl_field_new(size_t element_size, int width, int height);
cvl_field_t *cvl_field_i_new(int nelem, int width, int height);
cvl_field_t *cvl_field_f_new(int nelem, int width, int height);
void cvl_field_free(cvl_field_t *field);
size_t cvl_field_element_size(const cvl_field_t *field);
int cvl_field_width(const cvl_field_t *field);
int cvl_field_height(const cvl_field_t *field);
int cvl_field_size(const cvl_field_t *field);

void *cvl_field_array(cvl_field_t *field);
const void *cvl_field_const_array(const cvl_field_t *field);

void cvl_field_zero(cvl_field_t *field);
void cvl_field_copy(cvl_field_t *dst, const cvl_field_t *src);
cvl_field_t *cvl_field_clone(const cvl_field_t *field);

extern inline const void *cvl_field_get_i(const cvl_field_t *field, int i)
{
    cvl_assert(field != NULL);
    cvl_assert(i >= 0);
    cvl_assert(i < cvl_field_size(field));

    return &((unsigned char *)cvl_field_const_array(field))[cvl_field_element_size(field) * i];
}

extern inline const void *cvl_field_get(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);
    cvl_assert(x >= 0);
    cvl_assert(x < cvl_field_width(field));
    cvl_assert(y >= 0);
    cvl_assert(y < cvl_field_height(field));

    return cvl_field_get_i(field, y * cvl_field_width(field) + x);
}

extern inline const void *cvl_field_get_r(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);

    return cvl_field_get(field, 
	    cvl_reflect(x, cvl_field_width(field)), 
	    cvl_reflect(y, cvl_field_height(field)));
}

extern inline void cvl_field_set_i(cvl_field_t *field, int i, const void *e)
{
    cvl_assert(field != NULL);
    cvl_assert(e != NULL);
    cvl_assert(i >= 0);
    cvl_assert(i < cvl_field_size(field));

    memcpy(&((unsigned char *)cvl_field_array(field))[cvl_field_element_size(field) * i],
	    e, cvl_field_element_size(field));
}

extern inline void cvl_field_set(cvl_field_t *field, int x, int y, const void *e)
{
    cvl_assert(field != NULL);
    cvl_assert(e != NULL);
    cvl_assert(x >= 0);
    cvl_assert(x < cvl_field_width(field));
    cvl_assert(y >= 0);
    cvl_assert(y < cvl_field_height(field));

    cvl_field_set_i(field, y * cvl_field_width(field) + x, e);
}

extern inline const float *cvl_field_f_get_i(const cvl_field_t *field, int i)
{
    cvl_assert(field != NULL);
    cvl_assert(i >= 0);
    cvl_assert(i < cvl_field_size(field));

    return cvl_field_get_i(field, i);
}

extern inline const float *cvl_field_f_get(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);
    cvl_assert(x >= 0);
    cvl_assert(x < cvl_field_width(field));
    cvl_assert(y >= 0);
    cvl_assert(y < cvl_field_height(field));

    return cvl_field_get(field, x, y);
}

extern inline const float *cvl_field_f_get_r(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);

    return cvl_field_get_r(field, x, y);
}

extern inline const int *cvl_field_i_get_i(const cvl_field_t *field, int i)
{
    cvl_assert(field != NULL);
    cvl_assert(i >= 0);
    cvl_assert(i < cvl_field_size(field));

    return cvl_field_get_i(field, i);
}

extern inline const int *cvl_field_i_get(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);
    cvl_assert(x >= 0);
    cvl_assert(x < cvl_field_width(field));
    cvl_assert(y >= 0);
    cvl_assert(y < cvl_field_height(field));

    return cvl_field_get(field, x, y);
}

extern inline const int *cvl_field_i_get_r(const cvl_field_t *field, int x, int y)
{
    cvl_assert(field != NULL);

    return cvl_field_get_r(field, x, y);
}

void cvl_field_fill_rect(cvl_field_t *field, int x, int y, int w, int h, const void *e);
void cvl_field_copy_rect(cvl_field_t *dst, int dst_x, int dst_y, 
	const cvl_field_t *src, int src_x, int src_y, int rwidth, int rheight);

bool cvl_field_seek(FILE *f, size_t element_size, int width, int height, int newpos);
bool cvl_field_read(FILE *f, cvl_field_t **field);
bool cvl_field_read_knowntype(FILE *f, cvl_field_t **field, size_t element_size);
bool cvl_field_read_known(FILE *f, cvl_field_t *field);
bool cvl_field_write(FILE *f, const cvl_field_t *field);

#endif
