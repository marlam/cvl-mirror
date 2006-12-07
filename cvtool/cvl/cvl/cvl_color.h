/*
 * cvl_color.h
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

#ifndef CVL_COLOR_H
#define CVL_COLOR_H

#include <stdbool.h>

#include "cvl_pixel.h"
#include "cvl_frame.h"

typedef enum
{
    CVL_COLOR_SNOW =		0xfffafa,
    CVL_COLOR_GHOSTWHITE =	0xf8f8ff,
    CVL_COLOR_WHITESMOKE =	0xf5f5f5,
    CVL_COLOR_GAINSBORO =	0xdcdcdc,
    CVL_COLOR_FLORALWHITE =	0xfffaf0,
    CVL_COLOR_OLDLACE =		0xfdf5e6,
    CVL_COLOR_LINEN =		0xfaf0e6,
    CVL_COLOR_ANTIQUEWHITE =	0xfaebd7,
    CVL_COLOR_PAPAYAWHIP =	0xffefd5,
    CVL_COLOR_BLANCHEDALMOND =	0xffebcd,
    CVL_COLOR_BISQUE =		0xffe4c4,
    CVL_COLOR_PEACHPUFF =	0xffdab9,
    CVL_COLOR_NAVAJOWHITE =	0xffdead,
    CVL_COLOR_MOCCASIN =	0xffe4b5,
    CVL_COLOR_CORNSILK =	0xfff8dc,
    CVL_COLOR_IVORY =		0xfffff0,
    CVL_COLOR_LEMONCHIFFON =	0xfffacd,
    CVL_COLOR_SEASHELL =	0xfff5ee,
    CVL_COLOR_HONEYDEW =	0xf0fff0,
    CVL_COLOR_MINTCREAM =	0xf5fffa,
    CVL_COLOR_AZURE =		0xf0ffff,
    CVL_COLOR_ALICEBLUE =	0xf0f8ff,
    CVL_COLOR_LAVENDER =	0xe6e6fa,
    CVL_COLOR_LAVENDERBLUSH =	0xfff0f5,
    CVL_COLOR_MISTYROSE =	0xffe4e1,
    CVL_COLOR_WHITE =		0xffffff,
    CVL_COLOR_BLACK =		0x000000,
    CVL_COLOR_DARKSLATEGRAY =	0x2f4f4f,
    CVL_COLOR_DARKSLATEGREY =	0x2f4f4f,
    CVL_COLOR_DIMGRAY =		0x696969,
    CVL_COLOR_DIMGREY =		0x696969,
    CVL_COLOR_SLATEGRAY =	0x708090,
    CVL_COLOR_SLATEGREY =	0x708090,
    CVL_COLOR_LIGHTSLATEGRAY =	0x778899,
    CVL_COLOR_LIGHTSLATEGREY =	0x778899,
    CVL_COLOR_GRAY =		0xbebebe,
    CVL_COLOR_GREY =		0xbebebe,
    CVL_COLOR_LIGHTGREY =	0xd3d3d3,
    CVL_COLOR_LIGHTGRAY =	0xd3d3d3,
    CVL_COLOR_MIDNIGHTBLUE =	0x191970,
    CVL_COLOR_NAVY =		0x000080,
    CVL_COLOR_NAVYBLUE =	0x000080,
    CVL_COLOR_CORNFLOWERBLUE =	0x6495ed,
    CVL_COLOR_DARKSLATEBLUE =	0x483d8b,
    CVL_COLOR_SLATEBLUE =	0x6a5acd,
    CVL_COLOR_MEDIUMSLATEBLUE =	0x7b68ee,
    CVL_COLOR_LIGHTSLATEBLUE =	0x8470ff,
    CVL_COLOR_MEDIUMBLUE =	0x0000cd,
    CVL_COLOR_ROYALBLUE =	0x4169e1,
    CVL_COLOR_BLUE =		0x0000ff,
    CVL_COLOR_DODGERBLUE =	0x1e90ff,
    CVL_COLOR_DEEPSKYBLUE =	0x00bfff,
    CVL_COLOR_SKYBLUE =		0x87ceeb,
    CVL_COLOR_LIGHTSKYBLUE =	0x87cefa,
    CVL_COLOR_STEELBLUE =	0x4682b4,
    CVL_COLOR_LIGHTSTEELBLUE =	0xb0c4de,
    CVL_COLOR_LIGHTBLUE =	0xadd8e6,
    CVL_COLOR_POWDERBLUE =	0xb0e0e6,
    CVL_COLOR_PALETURQUOISE =	0xafeeee,
    CVL_COLOR_DARKTURQUOISE =	0x00ced1,
    CVL_COLOR_MEDIUMTURQUOISE =	0x48d1cc,
    CVL_COLOR_TURQUOISE =	0x40e0d0,
    CVL_COLOR_CYAN =		0x00ffff,
    CVL_COLOR_LIGHTCYAN =	0xe0ffff,
    CVL_COLOR_CADETBLUE =	0x5f9ea0,
    CVL_COLOR_MEDIUMAQUAMARINE = 0x66cdaa,
    CVL_COLOR_AQUAMARINE =	0x7fffd4,
    CVL_COLOR_DARKGREEN =	0x006400,
    CVL_COLOR_DARKOLIVEGREEN =	0x556b2f,
    CVL_COLOR_DARKSEAGREEN =	0x8fbc8f,
    CVL_COLOR_SEAGREEN =	0x2e8b57,
    CVL_COLOR_MEDIUMSEAGREEN =	0x3cb371,
    CVL_COLOR_LIGHTSEAGREEN =	0x20b2aa,
    CVL_COLOR_PALEGREEN =	0x98fb98,
    CVL_COLOR_SPRINGGREEN =	0x00ff7f,
    CVL_COLOR_LAWNGREEN =	0x7cfc00,
    CVL_COLOR_GREEN =		0x00ff00,
    CVL_COLOR_CHARTREUSE =	0x7fff00,
    CVL_COLOR_MEDIUMSPRINGGREEN = 0x00fa9a,
    CVL_COLOR_GREENYELLOW =	0xadff2f,
    CVL_COLOR_LIMEGREEN =	0x32cd32,
    CVL_COLOR_YELLOWGREEN =	0x9acd32,
    CVL_COLOR_FORESTGREEN =	0x228b22,
    CVL_COLOR_OLIVEDRAB =	0x6b8e23,
    CVL_COLOR_DARKKHAKI =	0xbdb76b,
    CVL_COLOR_KHAKI =		0xf0e68c,
    CVL_COLOR_PALEGOLDENROD =	0xeee8aa,
    CVL_COLOR_LIGHTGOLDENRODYELLOW = 0xfafad2,
    CVL_COLOR_LIGHTYELLOW =	0xffffe0,
    CVL_COLOR_YELLOW =		0xffff00,
    CVL_COLOR_GOLD =		0xffd700,
    CVL_COLOR_LIGHTGOLDENROD =	0xeedd82,
    CVL_COLOR_GOLDENROD =	0xdaa520,
    CVL_COLOR_DARKGOLDENROD =	0xb8860b,
    CVL_COLOR_ROSYBROWN =	0xbc8f8f,
    CVL_COLOR_INDIANRED =	0xcd5c5c,
    CVL_COLOR_SADDLEBROWN =	0x8b4513,
    CVL_COLOR_SIENNA =		0xa0522d,
    CVL_COLOR_PERU =		0xcd853f,
    CVL_COLOR_BURLYWOOD =	0xdeb887,
    CVL_COLOR_BEIGE =		0xf5f5dc,
    CVL_COLOR_WHEAT =		0xf5deb3,
    CVL_COLOR_SANDYBROWN =	0xf4a460,
    CVL_COLOR_TAN =		0xd2b48c,
    CVL_COLOR_CHOCOLATE =	0xd2691e,
    CVL_COLOR_FIREBRICK =	0xb22222,
    CVL_COLOR_BROWN =		0xa52a2a,
    CVL_COLOR_DARKSALMON =	0xe9967a,
    CVL_COLOR_SALMON =		0xfa8072,
    CVL_COLOR_LIGHTSALMON =	0xffa07a,
    CVL_COLOR_ORANGE =		0xffa500,
    CVL_COLOR_DARKORANGE =	0xff8c00,
    CVL_COLOR_CORAL =		0xff7f50,
    CVL_COLOR_LIGHTCORAL =	0xf08080,
    CVL_COLOR_TOMATO =		0xff6347,
    CVL_COLOR_ORANGERED =	0xff4500,
    CVL_COLOR_RED =		0xff0000,
    CVL_COLOR_HOTPINK =		0xff69b4,
    CVL_COLOR_DEEPPINK =	0xff1493,
    CVL_COLOR_PINK =		0xffc0cb,
    CVL_COLOR_LIGHTPINK =	0xffb6c1,
    CVL_COLOR_PALEVIOLETRED =	0xdb7093,
    CVL_COLOR_MAROON =		0xb03060,
    CVL_COLOR_MEDIUMVIOLETRED =	0xc71585,
    CVL_COLOR_VIOLETRED =	0xd02090,
    CVL_COLOR_MAGENTA =		0xff00ff,
    CVL_COLOR_VIOLET =		0xee82ee,
    CVL_COLOR_PLUM =		0xdda0dd,
    CVL_COLOR_ORCHID =		0xda70d6,
    CVL_COLOR_MEDIUMORCHID =	0xba55d3,
    CVL_COLOR_DARKORCHID =	0x9932cc,
    CVL_COLOR_DARKVIOLET =	0x9400d3,
    CVL_COLOR_BLUEVIOLET =	0x8a2be2,
    CVL_COLOR_PURPLE =		0xa020f0,
    CVL_COLOR_MEDIUMPURPLE =	0x9370db,
    CVL_COLOR_THISTLE =		0xd8bfd8,
    CVL_COLOR_SNOW1 =		0xfffafa,
    CVL_COLOR_SNOW2 =		0xeee9e9,
    CVL_COLOR_SNOW3 =		0xcdc9c9,
    CVL_COLOR_SNOW4 =		0x8b8989,
    CVL_COLOR_SEASHELL1 =	0xfff5ee,
    CVL_COLOR_SEASHELL2 =	0xeee5de,
    CVL_COLOR_SEASHELL3 =	0xcdc5bf,
    CVL_COLOR_SEASHELL4 =	0x8b8682,
    CVL_COLOR_ANTIQUEWHITE1 =	0xffefdb,
    CVL_COLOR_ANTIQUEWHITE2 =	0xeedfcc,
    CVL_COLOR_ANTIQUEWHITE3 =	0xcdc0b0,
    CVL_COLOR_ANTIQUEWHITE4 =	0x8b8378,
    CVL_COLOR_BISQUE1 =		0xffe4c4,
    CVL_COLOR_BISQUE2 =		0xeed5b7,
    CVL_COLOR_BISQUE3 =		0xcdb79e,
    CVL_COLOR_BISQUE4 =		0x8b7d6b,
    CVL_COLOR_PEACHPUFF1 =	0xffdab9,
    CVL_COLOR_PEACHPUFF2 =	0xeecbad,
    CVL_COLOR_PEACHPUFF3 =	0xcdaf95,
    CVL_COLOR_PEACHPUFF4 =	0x8b7765,
    CVL_COLOR_NAVAJOWHITE1 =	0xffdead,
    CVL_COLOR_NAVAJOWHITE2 =	0xeecfa1,
    CVL_COLOR_NAVAJOWHITE3 =	0xcdb38b,
    CVL_COLOR_NAVAJOWHITE4 =	0x8b795e,
    CVL_COLOR_LEMONCHIFFON1 =	0xfffacd,
    CVL_COLOR_LEMONCHIFFON2 =	0xeee9bf,
    CVL_COLOR_LEMONCHIFFON3 =	0xcdc9a5,
    CVL_COLOR_LEMONCHIFFON4 =	0x8b8970,
    CVL_COLOR_CORNSILK1 =	0xfff8dc,
    CVL_COLOR_CORNSILK2 =	0xeee8cd,
    CVL_COLOR_CORNSILK3 =	0xcdc8b1,
    CVL_COLOR_CORNSILK4 =	0x8b8878,
    CVL_COLOR_IVORY1 =		0xfffff0,
    CVL_COLOR_IVORY2 =		0xeeeee0,
    CVL_COLOR_IVORY3 =		0xcdcdc1,
    CVL_COLOR_IVORY4 =		0x8b8b83,
    CVL_COLOR_HONEYDEW1 =	0xf0fff0,
    CVL_COLOR_HONEYDEW2 =	0xe0eee0,
    CVL_COLOR_HONEYDEW3 =	0xc1cdc1,
    CVL_COLOR_HONEYDEW4 =	0x838b83,
    CVL_COLOR_LAVENDERBLUSH1 =	0xfff0f5,
    CVL_COLOR_LAVENDERBLUSH2 =	0xeee0e5,
    CVL_COLOR_LAVENDERBLUSH3 =	0xcdc1c5,
    CVL_COLOR_LAVENDERBLUSH4 =	0x8b8386,
    CVL_COLOR_MISTYROSE1 =	0xffe4e1,
    CVL_COLOR_MISTYROSE2 =	0xeed5d2,
    CVL_COLOR_MISTYROSE3 =	0xcdb7b5,
    CVL_COLOR_MISTYROSE4 =	0x8b7d7b,
    CVL_COLOR_AZURE1 =		0xf0ffff,
    CVL_COLOR_AZURE2 =		0xe0eeee,
    CVL_COLOR_AZURE3 =		0xc1cdcd,
    CVL_COLOR_AZURE4 =		0x838b8b,
    CVL_COLOR_SLATEBLUE1 =	0x836fff,
    CVL_COLOR_SLATEBLUE2 =	0x7a67ee,
    CVL_COLOR_SLATEBLUE3 =	0x6959cd,
    CVL_COLOR_SLATEBLUE4 =	0x473c8b,
    CVL_COLOR_ROYALBLUE1 =	0x4876ff,
    CVL_COLOR_ROYALBLUE2 =	0x436eee,
    CVL_COLOR_ROYALBLUE3 =	0x3a5fcd,
    CVL_COLOR_ROYALBLUE4 =	0x27408b,
    CVL_COLOR_BLUE1 =		0x0000ff,
    CVL_COLOR_BLUE2 =		0x0000ee,
    CVL_COLOR_BLUE3 =		0x0000cd,
    CVL_COLOR_BLUE4 =		0x00008b,
    CVL_COLOR_DODGERBLUE1 =	0x1e90ff,
    CVL_COLOR_DODGERBLUE2 =	0x1c86ee,
    CVL_COLOR_DODGERBLUE3 =	0x1874cd,
    CVL_COLOR_DODGERBLUE4 =	0x104e8b,
    CVL_COLOR_STEELBLUE1 =	0x63b8ff,
    CVL_COLOR_STEELBLUE2 =	0x5cacee,
    CVL_COLOR_STEELBLUE3 =	0x4f94cd,
    CVL_COLOR_STEELBLUE4 =	0x36648b,
    CVL_COLOR_DEEPSKYBLUE1 =	0x00bfff,
    CVL_COLOR_DEEPSKYBLUE2 =	0x00b2ee,
    CVL_COLOR_DEEPSKYBLUE3 =	0x009acd,
    CVL_COLOR_DEEPSKYBLUE4 =	0x00688b,
    CVL_COLOR_SKYBLUE1 =	0x87ceff,
    CVL_COLOR_SKYBLUE2 =	0x7ec0ee,
    CVL_COLOR_SKYBLUE3 =	0x6ca6cd,
    CVL_COLOR_SKYBLUE4 =	0x4a708b,
    CVL_COLOR_LIGHTSKYBLUE1 =	0xb0e2ff,
    CVL_COLOR_LIGHTSKYBLUE2 =	0xa4d3ee,
    CVL_COLOR_LIGHTSKYBLUE3 =	0x8db6cd,
    CVL_COLOR_LIGHTSKYBLUE4 =	0x607b8b,
    CVL_COLOR_SLATEGRAY1 =	0xc6e2ff,
    CVL_COLOR_SLATEGRAY2 =	0xb9d3ee,
    CVL_COLOR_SLATEGRAY3 =	0x9fb6cd,
    CVL_COLOR_SLATEGRAY4 =	0x6c7b8b,
    CVL_COLOR_LIGHTSTEELBLUE1 =	0xcae1ff,
    CVL_COLOR_LIGHTSTEELBLUE2 =	0xbcd2ee,
    CVL_COLOR_LIGHTSTEELBLUE3 =	0xa2b5cd,
    CVL_COLOR_LIGHTSTEELBLUE4 =	0x6e7b8b,
    CVL_COLOR_LIGHTBLUE1 =	0xbfefff,
    CVL_COLOR_LIGHTBLUE2 =	0xb2dfee,
    CVL_COLOR_LIGHTBLUE3 =	0x9ac0cd,
    CVL_COLOR_LIGHTBLUE4 =	0x68838b,
    CVL_COLOR_LIGHTCYAN1 =	0xe0ffff,
    CVL_COLOR_LIGHTCYAN2 =	0xd1eeee,
    CVL_COLOR_LIGHTCYAN3 =	0xb4cdcd,
    CVL_COLOR_LIGHTCYAN4 =	0x7a8b8b,
    CVL_COLOR_PALETURQUOISE1 =	0xbbffff,
    CVL_COLOR_PALETURQUOISE2 =	0xaeeeee,
    CVL_COLOR_PALETURQUOISE3 =	0x96cdcd,
    CVL_COLOR_PALETURQUOISE4 =	0x668b8b,
    CVL_COLOR_CADETBLUE1 =	0x98f5ff,
    CVL_COLOR_CADETBLUE2 =	0x8ee5ee,
    CVL_COLOR_CADETBLUE3 =	0x7ac5cd,
    CVL_COLOR_CADETBLUE4 =	0x53868b,
    CVL_COLOR_TURQUOISE1 =	0x00f5ff,
    CVL_COLOR_TURQUOISE2 =	0x00e5ee,
    CVL_COLOR_TURQUOISE3 =	0x00c5cd,
    CVL_COLOR_TURQUOISE4 =	0x00868b,
    CVL_COLOR_CYAN1 =		0x00ffff,
    CVL_COLOR_CYAN2 =		0x00eeee,
    CVL_COLOR_CYAN3 =		0x00cdcd,
    CVL_COLOR_CYAN4 =		0x008b8b,
    CVL_COLOR_DARKSLATEGRAY1 =	0x97ffff,
    CVL_COLOR_DARKSLATEGRAY2 =	0x8deeee,
    CVL_COLOR_DARKSLATEGRAY3 =	0x79cdcd,
    CVL_COLOR_DARKSLATEGRAY4 =	0x528b8b,
    CVL_COLOR_AQUAMARINE1 =	0x7fffd4,
    CVL_COLOR_AQUAMARINE2 =	0x76eec6,
    CVL_COLOR_AQUAMARINE3 =	0x66cdaa,
    CVL_COLOR_AQUAMARINE4 =	0x458b74,
    CVL_COLOR_DARKSEAGREEN1 =	0xc1ffc1,
    CVL_COLOR_DARKSEAGREEN2 =	0xb4eeb4,
    CVL_COLOR_DARKSEAGREEN3 =	0x9bcd9b,
    CVL_COLOR_DARKSEAGREEN4 =	0x698b69,
    CVL_COLOR_SEAGREEN1 =	0x54ff9f,
    CVL_COLOR_SEAGREEN2 =	0x4eee94,
    CVL_COLOR_SEAGREEN3 =	0x43cd80,
    CVL_COLOR_SEAGREEN4 =	0x2e8b57,
    CVL_COLOR_PALEGREEN1 =	0x9aff9a,
    CVL_COLOR_PALEGREEN2 =	0x90ee90,
    CVL_COLOR_PALEGREEN3 =	0x7ccd7c,
    CVL_COLOR_PALEGREEN4 =	0x548b54,
    CVL_COLOR_SPRINGGREEN1 =	0x00ff7f,
    CVL_COLOR_SPRINGGREEN2 =	0x00ee76,
    CVL_COLOR_SPRINGGREEN3 =	0x00cd66,
    CVL_COLOR_SPRINGGREEN4 =	0x008b45,
    CVL_COLOR_GREEN1 =		0x00ff00,
    CVL_COLOR_GREEN2 =		0x00ee00,
    CVL_COLOR_GREEN3 =		0x00cd00,
    CVL_COLOR_GREEN4 =		0x008b00,
    CVL_COLOR_CHARTREUSE1 =	0x7fff00,
    CVL_COLOR_CHARTREUSE2 =	0x76ee00,
    CVL_COLOR_CHARTREUSE3 =	0x66cd00,
    CVL_COLOR_CHARTREUSE4 =	0x458b00,
    CVL_COLOR_OLIVEDRAB1 =	0xc0ff3e,
    CVL_COLOR_OLIVEDRAB2 =	0xb3ee3a,
    CVL_COLOR_OLIVEDRAB3 =	0x9acd32,
    CVL_COLOR_OLIVEDRAB4 =	0x698b22,
    CVL_COLOR_DARKOLIVEGREEN1 =	0xcaff70,
    CVL_COLOR_DARKOLIVEGREEN2 =	0xbcee68,
    CVL_COLOR_DARKOLIVEGREEN3 =	0xa2cd5a,
    CVL_COLOR_DARKOLIVEGREEN4 =	0x6e8b3d,
    CVL_COLOR_KHAKI1 =		0xfff68f,
    CVL_COLOR_KHAKI2 =		0xeee685,
    CVL_COLOR_KHAKI3 =		0xcdc673,
    CVL_COLOR_KHAKI4 =		0x8b864e,
    CVL_COLOR_LIGHTGOLDENROD1 =	0xffec8b,
    CVL_COLOR_LIGHTGOLDENROD2 =	0xeedc82,
    CVL_COLOR_LIGHTGOLDENROD3 =	0xcdbe70,
    CVL_COLOR_LIGHTGOLDENROD4 =	0x8b814c,
    CVL_COLOR_LIGHTYELLOW1 =	0xffffe0,
    CVL_COLOR_LIGHTYELLOW2 =	0xeeeed1,
    CVL_COLOR_LIGHTYELLOW3 =	0xcdcdb4,
    CVL_COLOR_LIGHTYELLOW4 =	0x8b8b7a,
    CVL_COLOR_YELLOW1 =		0xffff00,
    CVL_COLOR_YELLOW2 =		0xeeee00,
    CVL_COLOR_YELLOW3 =		0xcdcd00,
    CVL_COLOR_YELLOW4 =		0x8b8b00,
    CVL_COLOR_GOLD1 =		0xffd700,
    CVL_COLOR_GOLD2 =		0xeec900,
    CVL_COLOR_GOLD3 =		0xcdad00,
    CVL_COLOR_GOLD4 =		0x8b7500,
    CVL_COLOR_GOLDENROD1 =	0xffc125,
    CVL_COLOR_GOLDENROD2 =	0xeeb422,
    CVL_COLOR_GOLDENROD3 =	0xcd9b1d,
    CVL_COLOR_GOLDENROD4 =	0x8b6914,
    CVL_COLOR_DARKGOLDENROD1 =	0xffb90f,
    CVL_COLOR_DARKGOLDENROD2 =	0xeead0e,
    CVL_COLOR_DARKGOLDENROD3 =	0xcd950c,
    CVL_COLOR_DARKGOLDENROD4 =	0x8b6508,
    CVL_COLOR_ROSYBROWN1 =	0xffc1c1,
    CVL_COLOR_ROSYBROWN2 =	0xeeb4b4,
    CVL_COLOR_ROSYBROWN3 =	0xcd9b9b,
    CVL_COLOR_ROSYBROWN4 =	0x8b6969,
    CVL_COLOR_INDIANRED1 =	0xff6a6a,
    CVL_COLOR_INDIANRED2 =	0xee6363,
    CVL_COLOR_INDIANRED3 =	0xcd5555,
    CVL_COLOR_INDIANRED4 =	0x8b3a3a,
    CVL_COLOR_SIENNA1 =		0xff8247,
    CVL_COLOR_SIENNA2 =		0xee7942,
    CVL_COLOR_SIENNA3 =		0xcd6839,
    CVL_COLOR_SIENNA4 =		0x8b4726,
    CVL_COLOR_BURLYWOOD1 =	0xffd39b,
    CVL_COLOR_BURLYWOOD2 =	0xeec591,
    CVL_COLOR_BURLYWOOD3 =	0xcdaa7d,
    CVL_COLOR_BURLYWOOD4 =	0x8b7355,
    CVL_COLOR_WHEAT1 =		0xffe7ba,
    CVL_COLOR_WHEAT2 =		0xeed8ae,
    CVL_COLOR_WHEAT3 =		0xcdba96,
    CVL_COLOR_WHEAT4 =		0x8b7e66,
    CVL_COLOR_TAN1 =		0xffa54f,
    CVL_COLOR_TAN2 =		0xee9a49,
    CVL_COLOR_TAN3 =		0xcd853f,
    CVL_COLOR_TAN4 =		0x8b5a2b,
    CVL_COLOR_CHOCOLATE1 =	0xff7f24,
    CVL_COLOR_CHOCOLATE2 =	0xee7621,
    CVL_COLOR_CHOCOLATE3 =	0xcd661d,
    CVL_COLOR_CHOCOLATE4 =	0x8b4513,
    CVL_COLOR_FIREBRICK1 =	0xff3030,
    CVL_COLOR_FIREBRICK2 =	0xee2c2c,
    CVL_COLOR_FIREBRICK3 =	0xcd2626,
    CVL_COLOR_FIREBRICK4 =	0x8b1a1a,
    CVL_COLOR_BROWN1 =		0xff4040,
    CVL_COLOR_BROWN2 =		0xee3b3b,
    CVL_COLOR_BROWN3 =		0xcd3333,
    CVL_COLOR_BROWN4 =		0x8b2323,
    CVL_COLOR_SALMON1 =		0xff8c69,
    CVL_COLOR_SALMON2 =		0xee8262,
    CVL_COLOR_SALMON3 =		0xcd7054,
    CVL_COLOR_SALMON4 =		0x8b4c39,
    CVL_COLOR_LIGHTSALMON1 =	0xffa07a,
    CVL_COLOR_LIGHTSALMON2 =	0xee9572,
    CVL_COLOR_LIGHTSALMON3 =	0xcd8162,
    CVL_COLOR_LIGHTSALMON4 =	0x8b5742,
    CVL_COLOR_ORANGE1 =		0xffa500,
    CVL_COLOR_ORANGE2 =		0xee9a00,
    CVL_COLOR_ORANGE3 =		0xcd8500,
    CVL_COLOR_ORANGE4 =		0x8b5a00,
    CVL_COLOR_DARKORANGE1 =	0xff7f00,
    CVL_COLOR_DARKORANGE2 =	0xee7600,
    CVL_COLOR_DARKORANGE3 =	0xcd6600,
    CVL_COLOR_DARKORANGE4 =	0x8b4500,
    CVL_COLOR_CORAL1 =		0xff7256,
    CVL_COLOR_CORAL2 =		0xee6a50,
    CVL_COLOR_CORAL3 =		0xcd5b45,
    CVL_COLOR_CORAL4 =		0x8b3e2f,
    CVL_COLOR_TOMATO1 =		0xff6347,
    CVL_COLOR_TOMATO2 =		0xee5c42,
    CVL_COLOR_TOMATO3 =		0xcd4f39,
    CVL_COLOR_TOMATO4 =		0x8b3626,
    CVL_COLOR_ORANGERED1 =	0xff4500,
    CVL_COLOR_ORANGERED2 =	0xee4000,
    CVL_COLOR_ORANGERED3 =	0xcd3700,
    CVL_COLOR_ORANGERED4 =	0x8b2500,
    CVL_COLOR_RED1 =		0xff0000,
    CVL_COLOR_RED2 =		0xee0000,
    CVL_COLOR_RED3 =		0xcd0000,
    CVL_COLOR_RED4 =		0x8b0000,
    CVL_COLOR_DEEPPINK1 =	0xff1493,
    CVL_COLOR_DEEPPINK2 =	0xee1289,
    CVL_COLOR_DEEPPINK3 =	0xcd1076,
    CVL_COLOR_DEEPPINK4 =	0x8b0a50,
    CVL_COLOR_HOTPINK1 =	0xff6eb4,
    CVL_COLOR_HOTPINK2 =	0xee6aa7,
    CVL_COLOR_HOTPINK3 =	0xcd6090,
    CVL_COLOR_HOTPINK4 =	0x8b3a62,
    CVL_COLOR_PINK1 =		0xffb5c5,
    CVL_COLOR_PINK2 =		0xeea9b8,
    CVL_COLOR_PINK3 =		0xcd919e,
    CVL_COLOR_PINK4 =		0x8b636c,
    CVL_COLOR_LIGHTPINK1 =	0xffaeb9,
    CVL_COLOR_LIGHTPINK2 =	0xeea2ad,
    CVL_COLOR_LIGHTPINK3 =	0xcd8c95,
    CVL_COLOR_LIGHTPINK4 =	0x8b5f65,
    CVL_COLOR_PALEVIOLETRED1 =	0xff82ab,
    CVL_COLOR_PALEVIOLETRED2 =	0xee799f,
    CVL_COLOR_PALEVIOLETRED3 =	0xcd6889,
    CVL_COLOR_PALEVIOLETRED4 =	0x8b475d,
    CVL_COLOR_MAROON1 =		0xff34b3,
    CVL_COLOR_MAROON2 =		0xee30a7,
    CVL_COLOR_MAROON3 =		0xcd2990,
    CVL_COLOR_MAROON4 =		0x8b1c62,
    CVL_COLOR_VIOLETRED1 =	0xff3e96,
    CVL_COLOR_VIOLETRED2 =	0xee3a8c,
    CVL_COLOR_VIOLETRED3 =	0xcd3278,
    CVL_COLOR_VIOLETRED4 =	0x8b2252,
    CVL_COLOR_MAGENTA1 =	0xff00ff,
    CVL_COLOR_MAGENTA2 =	0xee00ee,
    CVL_COLOR_MAGENTA3 =	0xcd00cd,
    CVL_COLOR_MAGENTA4 =	0x8b008b,
    CVL_COLOR_ORCHID1 =		0xff83fa,
    CVL_COLOR_ORCHID2 =		0xee7ae9,
    CVL_COLOR_ORCHID3 =		0xcd69c9,
    CVL_COLOR_ORCHID4 =		0x8b4789,
    CVL_COLOR_PLUM1 =		0xffbbff,
    CVL_COLOR_PLUM2 =		0xeeaeee,
    CVL_COLOR_PLUM3 =		0xcd96cd,
    CVL_COLOR_PLUM4 =		0x8b668b,
    CVL_COLOR_MEDIUMORCHID1 =	0xe066ff,
    CVL_COLOR_MEDIUMORCHID2 =	0xd15fee,
    CVL_COLOR_MEDIUMORCHID3 =	0xb452cd,
    CVL_COLOR_MEDIUMORCHID4 =	0x7a378b,
    CVL_COLOR_DARKORCHID1 =	0xbf3eff,
    CVL_COLOR_DARKORCHID2 =	0xb23aee,
    CVL_COLOR_DARKORCHID3 =	0x9a32cd,
    CVL_COLOR_DARKORCHID4 =	0x68228b,
    CVL_COLOR_PURPLE1 =		0x9b30ff,
    CVL_COLOR_PURPLE2 =		0x912cee,
    CVL_COLOR_PURPLE3 =		0x7d26cd,
    CVL_COLOR_PURPLE4 =		0x551a8b,
    CVL_COLOR_MEDIUMPURPLE1 =	0xab82ff,
    CVL_COLOR_MEDIUMPURPLE2 =	0x9f79ee,
    CVL_COLOR_MEDIUMPURPLE3 =	0x8968cd,
    CVL_COLOR_MEDIUMPURPLE4 =	0x5d478b,
    CVL_COLOR_THISTLE1 =	0xffe1ff,
    CVL_COLOR_THISTLE2 =	0xeed2ee,
    CVL_COLOR_THISTLE3 =	0xcdb5cd,
    CVL_COLOR_THISTLE4 =	0x8b7b8b,
    CVL_COLOR_GRAY0 =		0x000000,
    CVL_COLOR_GREY0 =		0x000000,
    CVL_COLOR_GRAY1 =		0x030303,
    CVL_COLOR_GREY1 =		0x030303,
    CVL_COLOR_GRAY2 =		0x050505,
    CVL_COLOR_GREY2 =		0x050505,
    CVL_COLOR_GRAY3 =		0x080808,
    CVL_COLOR_GREY3 =		0x080808,
    CVL_COLOR_GRAY4 =		0x0a0a0a,
    CVL_COLOR_GREY4 =		0x0a0a0a,
    CVL_COLOR_GRAY5 =		0x0d0d0d,
    CVL_COLOR_GREY5 =		0x0d0d0d,
    CVL_COLOR_GRAY6 =		0x0f0f0f,
    CVL_COLOR_GREY6 =		0x0f0f0f,
    CVL_COLOR_GRAY7 =		0x121212,
    CVL_COLOR_GREY7 =		0x121212,
    CVL_COLOR_GRAY8 =		0x141414,
    CVL_COLOR_GREY8 =		0x141414,
    CVL_COLOR_GRAY9 =		0x171717,
    CVL_COLOR_GREY9 =		0x171717,
    CVL_COLOR_GRAY10 =		0x1a1a1a,
    CVL_COLOR_GREY10 =		0x1a1a1a,
    CVL_COLOR_GRAY11 =		0x1c1c1c,
    CVL_COLOR_GREY11 =		0x1c1c1c,
    CVL_COLOR_GRAY12 =		0x1f1f1f,
    CVL_COLOR_GREY12 =		0x1f1f1f,
    CVL_COLOR_GRAY13 =		0x212121,
    CVL_COLOR_GREY13 =		0x212121,
    CVL_COLOR_GRAY14 =		0x242424,
    CVL_COLOR_GREY14 =		0x242424,
    CVL_COLOR_GRAY15 =		0x262626,
    CVL_COLOR_GREY15 =		0x262626,
    CVL_COLOR_GRAY16 =		0x292929,
    CVL_COLOR_GREY16 =		0x292929,
    CVL_COLOR_GRAY17 =		0x2b2b2b,
    CVL_COLOR_GREY17 =		0x2b2b2b,
    CVL_COLOR_GRAY18 =		0x2e2e2e,
    CVL_COLOR_GREY18 =		0x2e2e2e,
    CVL_COLOR_GRAY19 =		0x303030,
    CVL_COLOR_GREY19 =		0x303030,
    CVL_COLOR_GRAY20 =		0x333333,
    CVL_COLOR_GREY20 =		0x333333,
    CVL_COLOR_GRAY21 =		0x363636,
    CVL_COLOR_GREY21 =		0x363636,
    CVL_COLOR_GRAY22 =		0x383838,
    CVL_COLOR_GREY22 =		0x383838,
    CVL_COLOR_GRAY23 =		0x3b3b3b,
    CVL_COLOR_GREY23 =		0x3b3b3b,
    CVL_COLOR_GRAY24 =		0x3d3d3d,
    CVL_COLOR_GREY24 =		0x3d3d3d,
    CVL_COLOR_GRAY25 =		0x404040,
    CVL_COLOR_GREY25 =		0x404040,
    CVL_COLOR_GRAY26 =		0x424242,
    CVL_COLOR_GREY26 =		0x424242,
    CVL_COLOR_GRAY27 =		0x454545,
    CVL_COLOR_GREY27 =		0x454545,
    CVL_COLOR_GRAY28 =		0x474747,
    CVL_COLOR_GREY28 =		0x474747,
    CVL_COLOR_GRAY29 =		0x4a4a4a,
    CVL_COLOR_GREY29 =		0x4a4a4a,
    CVL_COLOR_GRAY30 =		0x4d4d4d,
    CVL_COLOR_GREY30 =		0x4d4d4d,
    CVL_COLOR_GRAY31 =		0x4f4f4f,
    CVL_COLOR_GREY31 =		0x4f4f4f,
    CVL_COLOR_GRAY32 =		0x525252,
    CVL_COLOR_GREY32 =		0x525252,
    CVL_COLOR_GRAY33 =		0x545454,
    CVL_COLOR_GREY33 =		0x545454,
    CVL_COLOR_GRAY34 =		0x575757,
    CVL_COLOR_GREY34 =		0x575757,
    CVL_COLOR_GRAY35 =		0x595959,
    CVL_COLOR_GREY35 =		0x595959,
    CVL_COLOR_GRAY36 =		0x5c5c5c,
    CVL_COLOR_GREY36 =		0x5c5c5c,
    CVL_COLOR_GRAY37 =		0x5e5e5e,
    CVL_COLOR_GREY37 =		0x5e5e5e,
    CVL_COLOR_GRAY38 =		0x616161,
    CVL_COLOR_GREY38 =		0x616161,
    CVL_COLOR_GRAY39 =		0x636363,
    CVL_COLOR_GREY39 =		0x636363,
    CVL_COLOR_GRAY40 =		0x666666,
    CVL_COLOR_GREY40 =		0x666666,
    CVL_COLOR_GRAY41 =		0x696969,
    CVL_COLOR_GREY41 =		0x696969,
    CVL_COLOR_GRAY42 =		0x6b6b6b,
    CVL_COLOR_GREY42 =		0x6b6b6b,
    CVL_COLOR_GRAY43 =		0x6e6e6e,
    CVL_COLOR_GREY43 =		0x6e6e6e,
    CVL_COLOR_GRAY44 =		0x707070,
    CVL_COLOR_GREY44 =		0x707070,
    CVL_COLOR_GRAY45 =		0x737373,
    CVL_COLOR_GREY45 =		0x737373,
    CVL_COLOR_GRAY46 =		0x757575,
    CVL_COLOR_GREY46 =		0x757575,
    CVL_COLOR_GRAY47 =		0x787878,
    CVL_COLOR_GREY47 =		0x787878,
    CVL_COLOR_GRAY48 =		0x7a7a7a,
    CVL_COLOR_GREY48 =		0x7a7a7a,
    CVL_COLOR_GRAY49 =		0x7d7d7d,
    CVL_COLOR_GREY49 =		0x7d7d7d,
    CVL_COLOR_GRAY50 =		0x7f7f7f,
    CVL_COLOR_GREY50 =		0x7f7f7f,
    CVL_COLOR_GRAY51 =		0x828282,
    CVL_COLOR_GREY51 =		0x828282,
    CVL_COLOR_GRAY52 =		0x858585,
    CVL_COLOR_GREY52 =		0x858585,
    CVL_COLOR_GRAY53 =		0x878787,
    CVL_COLOR_GREY53 =		0x878787,
    CVL_COLOR_GRAY54 =		0x8a8a8a,
    CVL_COLOR_GREY54 =		0x8a8a8a,
    CVL_COLOR_GRAY55 =		0x8c8c8c,
    CVL_COLOR_GREY55 =		0x8c8c8c,
    CVL_COLOR_GRAY56 =		0x8f8f8f,
    CVL_COLOR_GREY56 =		0x8f8f8f,
    CVL_COLOR_GRAY57 =		0x919191,
    CVL_COLOR_GREY57 =		0x919191,
    CVL_COLOR_GRAY58 =		0x949494,
    CVL_COLOR_GREY58 =		0x949494,
    CVL_COLOR_GRAY59 =		0x969696,
    CVL_COLOR_GREY59 =		0x969696,
    CVL_COLOR_GRAY60 =		0x999999,
    CVL_COLOR_GREY60 =		0x999999,
    CVL_COLOR_GRAY61 =		0x9c9c9c,
    CVL_COLOR_GREY61 =		0x9c9c9c,
    CVL_COLOR_GRAY62 =		0x9e9e9e,
    CVL_COLOR_GREY62 =		0x9e9e9e,
    CVL_COLOR_GRAY63 =		0xa1a1a1,
    CVL_COLOR_GREY63 =		0xa1a1a1,
    CVL_COLOR_GRAY64 =		0xa3a3a3,
    CVL_COLOR_GREY64 =		0xa3a3a3,
    CVL_COLOR_GRAY65 =		0xa6a6a6,
    CVL_COLOR_GREY65 =		0xa6a6a6,
    CVL_COLOR_GRAY66 =		0xa8a8a8,
    CVL_COLOR_GREY66 =		0xa8a8a8,
    CVL_COLOR_GRAY67 =		0xababab,
    CVL_COLOR_GREY67 =		0xababab,
    CVL_COLOR_GRAY68 =		0xadadad,
    CVL_COLOR_GREY68 =		0xadadad,
    CVL_COLOR_GRAY69 =		0xb0b0b0,
    CVL_COLOR_GREY69 =		0xb0b0b0,
    CVL_COLOR_GRAY70 =		0xb3b3b3,
    CVL_COLOR_GREY70 =		0xb3b3b3,
    CVL_COLOR_GRAY71 =		0xb5b5b5,
    CVL_COLOR_GREY71 =		0xb5b5b5,
    CVL_COLOR_GRAY72 =		0xb8b8b8,
    CVL_COLOR_GREY72 =		0xb8b8b8,
    CVL_COLOR_GRAY73 =		0xbababa,
    CVL_COLOR_GREY73 =		0xbababa,
    CVL_COLOR_GRAY74 =		0xbdbdbd,
    CVL_COLOR_GREY74 =		0xbdbdbd,
    CVL_COLOR_GRAY75 =		0xbfbfbf,
    CVL_COLOR_GREY75 =		0xbfbfbf,
    CVL_COLOR_GRAY76 =		0xc2c2c2,
    CVL_COLOR_GREY76 =		0xc2c2c2,
    CVL_COLOR_GRAY77 =		0xc4c4c4,
    CVL_COLOR_GREY77 =		0xc4c4c4,
    CVL_COLOR_GRAY78 =		0xc7c7c7,
    CVL_COLOR_GREY78 =		0xc7c7c7,
    CVL_COLOR_GRAY79 =		0xc9c9c9,
    CVL_COLOR_GREY79 =		0xc9c9c9,
    CVL_COLOR_GRAY80 =		0xcccccc,
    CVL_COLOR_GREY80 =		0xcccccc,
    CVL_COLOR_GRAY81 =		0xcfcfcf,
    CVL_COLOR_GREY81 =		0xcfcfcf,
    CVL_COLOR_GRAY82 =		0xd1d1d1,
    CVL_COLOR_GREY82 =		0xd1d1d1,
    CVL_COLOR_GRAY83 =		0xd4d4d4,
    CVL_COLOR_GREY83 =		0xd4d4d4,
    CVL_COLOR_GRAY84 =		0xd6d6d6,
    CVL_COLOR_GREY84 =		0xd6d6d6,
    CVL_COLOR_GRAY85 =		0xd9d9d9,
    CVL_COLOR_GREY85 =		0xd9d9d9,
    CVL_COLOR_GRAY86 =		0xdbdbdb,
    CVL_COLOR_GREY86 =		0xdbdbdb,
    CVL_COLOR_GRAY87 =		0xdedede,
    CVL_COLOR_GREY87 =		0xdedede,
    CVL_COLOR_GRAY88 =		0xe0e0e0,
    CVL_COLOR_GREY88 =		0xe0e0e0,
    CVL_COLOR_GRAY89 =		0xe3e3e3,
    CVL_COLOR_GREY89 =		0xe3e3e3,
    CVL_COLOR_GRAY90 =		0xe5e5e5,
    CVL_COLOR_GREY90 =		0xe5e5e5,
    CVL_COLOR_GRAY91 =		0xe8e8e8,
    CVL_COLOR_GREY91 =		0xe8e8e8,
    CVL_COLOR_GRAY92 =		0xebebeb,
    CVL_COLOR_GREY92 =		0xebebeb,
    CVL_COLOR_GRAY93 =		0xededed,
    CVL_COLOR_GREY93 =		0xededed,
    CVL_COLOR_GRAY94 =		0xf0f0f0,
    CVL_COLOR_GREY94 =		0xf0f0f0,
    CVL_COLOR_GRAY95 =		0xf2f2f2,
    CVL_COLOR_GREY95 =		0xf2f2f2,
    CVL_COLOR_GRAY96 =		0xf5f5f5,
    CVL_COLOR_GREY96 =		0xf5f5f5,
    CVL_COLOR_GRAY97 =		0xf7f7f7,
    CVL_COLOR_GREY97 =		0xf7f7f7,
    CVL_COLOR_GRAY98 =		0xfafafa,
    CVL_COLOR_GREY98 =		0xfafafa,
    CVL_COLOR_GRAY99 =		0xfcfcfc,
    CVL_COLOR_GREY99 =		0xfcfcfc,
    CVL_COLOR_GRAY100 =		0xffffff,
    CVL_COLOR_GREY100 =		0xffffff,
    CVL_COLOR_DARKGREY =	0xa9a9a9,
    CVL_COLOR_DARKGRAY =	0xa9a9a9,
    CVL_COLOR_DARKBLUE =	0x00008b,
    CVL_COLOR_DARKCYAN =	0x008b8b,
    CVL_COLOR_DARKMAGENTA =	0x8b008b,
    CVL_COLOR_DARKRED =		0x8b0000,
    CVL_COLOR_LIGHTGREEN =	0x90ee90
} cvl_color_t;


cvl_pixel_t cvl_color_to_pixel(cvl_color_t color, cvl_pixel_type_t pixel_type);
extern inline cvl_pixel_t cvl_color_to_pixel(cvl_color_t color, cvl_pixel_type_t pixel_type)
{
    return (pixel_type == CVL_PIXEL_RGB) ? color : 
	((pixel_type == CVL_PIXEL_GRAY) ? cvl_pixel_rgb_to_gray(color) : cvl_pixel_rgb_to_yuv(color));
}

bool cvl_color_from_string(const char *s, cvl_color_t *color);

void cvl_rgb_to_hsl(cvl_pixel_t rgb, float *H, float *S, float *L);
cvl_pixel_t cvl_hsl_to_rgb(float H, float S, float L);
void cvl_srgb_to_cielab(cvl_pixel_t srgb, float *L, float *a, float *b);

void cvl_color_adjust(cvl_frame_t *frame, 
	float hue, float saturation, float lightness, float contrast);
void cvl_gamma_correct(cvl_frame_t *frame, float gamma);
void cvl_gamma_correct_rgb(cvl_frame_t *frame, float gamma_r, float gamma_g, float gamma_b);
void cvl_invert(cvl_frame_t *frame);

void cvl_abs_histogram(cvl_frame_t *frame, int channel, int *count);
void cvl_histogram_sum(int *count, int *sum);
void cvl_rel_histogram(cvl_frame_t *frame, int *abs_hist, float *rel_hist);
void cvl_equalize_histogram(cvl_frame_t *frame);

void cvl_binarize_global_threshold(cvl_frame_t *frame, int threshold);
int cvl_binarize_get_threshold_iterative(cvl_frame_t *frame);
int cvl_binarize_get_threshold_otsu(cvl_frame_t *frame);
typedef enum
{
    CVL_BINARIZE_LOCAL_THRESHOLD_MEAN = 0,
    CVL_BINARIZE_LOCAL_THRESHOLD_MEDIAN = 1,
    CVL_BINARIZE_LOCAL_THRESHOLD_MINMAX = 2
} cvl_binarize_local_threshold_type_t;
void cvl_binarize_local_threshold(cvl_frame_t *frame, cvl_binarize_local_threshold_type_t type, int k, int C);
void cvl_binarize_hysterese(cvl_frame_t *frame, int tl, int th);

#endif
