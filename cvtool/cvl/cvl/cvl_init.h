/*
 * cvl_init.h
 * 
 * This file is part of CVL, a computer vision library.
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

#ifndef CVL_INIT_H
#define CVL_INIT_H

extern CVL_EXPORT void cvl_init(void);
extern CVL_EXPORT void cvl_deinit(void);
extern CVL_EXPORT const char *cvl_version(int *major, int *minor, int *patch);

#endif
