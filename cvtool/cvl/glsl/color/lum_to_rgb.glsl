/*
 * lum_to_rgb.glsl
 * 
 * This file is part of CVL, a computer vision library.
 *
 * Copyright (C) 2007, 2008  Martin Lambers <marlam@marlam.de>
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

#version 110

uniform sampler2D tex;

void main()
{
    const float d65_x = 0.31271;
    const float d65_y = 0.32902;
    float y = texture2D(tex, gl_TexCoord[0].xy).r;
    float x = y * (d65_x / d65_y);
    float z = min(1.0, y * (1.0 - d65_x - d65_y) / d65_y);
    
    // We use the D65 reference white for the RGB values.
    // The computation is exactly the same that is used by pfstools-1.6.2.
    mat3 M = mat3( 3.240708, -1.537259, -0.498570,
	          -0.969257,  1.875995,  0.041555,
		   0.055636, -0.203996,  1.057069);
    vec3 rgb = vec3(x, y, z) * M;

    rgb.r = (rgb.r <= 0.0031308 ? (rgb.r * 12.92) : (1.055 * pow(rgb.r, 1.0 / 2.4) - 0.055));
    rgb.g = (rgb.g <= 0.0031308 ? (rgb.g * 12.92) : (1.055 * pow(rgb.g, 1.0 / 2.4) - 0.055));
    rgb.b = (rgb.b <= 0.0031308 ? (rgb.b * 12.92) : (1.055 * pow(rgb.b, 1.0 / 2.4) - 0.055));

    gl_FragColor = vec4(rgb, 0.0);
}
