dnl configure.ac
dnl Process this file with autoconf to produce a configure script.
#
# This file is part of cvlview, an image viewer using the CVL library.
#
# Copyright (C) 2007, 2008, 2009, 2010  Martin Lambers <marlam@marlam.de>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

dnl Autotools init stuff
AC_PREREQ([2.65])
AC_INIT([CVLView], [1.0.2], [marlam@marlam.de])
AC_CONFIG_SRCDIR([src/cvlview.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CANONICAL_TARGET
AC_USE_SYSTEM_EXTENSIONS
AC_SYS_LARGEFILE
AM_INIT_AUTOMAKE([1.11.1 color-tests silent-rules no-texinfo.tex -Wall -Wno-portability])
AM_SILENT_RULES([yes])
LT_PREREQ([2.2.6])
LT_INIT([disable-static])
AC_PROG_CC
AC_PROG_CC_C99
gl_EARLY
AC_PROG_CXX
AC_PROG_INSTALL
AC_C_BIGENDIAN

dnl System
case "${target}" in *-*-mingw32*) w32=yes ;; *) w32=no ;; esac
AM_CONDITIONAL([W32], [test "$w32" = "yes"])
if test "$w32" = "yes"; then
	AC_CHECK_TOOL([WINDRES], [windres], [:], [$PATH])
	if test "$WINDRES" = ":"; then
		AC_MSG_ERROR([windres not found])
	fi
fi

dnl gnulib 
gl_INIT

dnl mhlib
AC_CHECK_FUNCS([backtrace sigaction])
AC_SEARCH_LIBS([clock_gettime], [rt])

dnl Math library
AC_SEARCH_LIBS([sqrtf], [m])

dnl GLEW (used only by CVL)
PKG_CHECK_MODULES([GLEW], [glew >= 1.5.0])

dnl CVL
AM_CVL([1], [0], [0])
if test "$HAVE_LIBCVL" != "yes"; then
	AC_MSG_ERROR([libcvl >= 1.0.0 not found])
fi

dnl Qt4
PKG_CHECK_MODULES([QTOPENGL], [QtOpenGL >= 0.0])
RCC=""
AC_ARG_VAR([RCC], [rcc command])
MOC=""
AC_ARG_VAR([MOC], [moc command])
AC_CHECK_TOOLS([RCC], [rcc-qt4 rcc])
AC_CHECK_TOOLS([MOC], [moc-qt4 moc])

dnl Global #defines for all source files
AH_VERBATIM([UNUSED],
[/* Let gcc know about unused variables to suppress warnings.
   Disable this feature for other compilers. */
#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#  define __attribute__(x)
# else
#  define __attribute__(x) __attribute__(x)
# endif
#endif
#ifndef UNUSED
# define UNUSED __attribute__ ((__unused__))
#endif])
AH_VERBATIM([W32_NATIVE],
[/* Define to 1 if the native W32 API should be used. */
#if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
#define W32_NATIVE 1
#endif])

dnl Ouput
AC_CONFIG_FILES([Makefile	\
	gnulib/Makefile		\
	mhlib/Makefile		\
	gllib/Makefile		\
	src/Makefile		\
	doc/Makefile		\
	])
AC_OUTPUT
