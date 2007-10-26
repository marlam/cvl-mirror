/*
 * mix.glsl
 * 
 * This file is part of CVL, a computer vision library.
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

#version 120

const int n = $n;
uniform sampler2D srcs[n];
uniform float total_weight;
uniform float w[n];

void main()
{
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < n; i++)
    {
	gl_FragColor += (w[i] / total_weight) * texture2D(srcs[i], gl_TexCoord[0].xy);
    }
}