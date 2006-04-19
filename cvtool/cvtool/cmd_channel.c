/*
 * cmd_channel.c
 * 
 * This file is part of cvtool, a computer vision tool.
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

#include "config.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <cvl/cvl.h>

#include "options.h"


void cmd_channel_print_help(void)
{
    cvl_msg_fmt_req(
	    "channel [-g|--gray] -c|--channel=r|g|b\n"
	    "\n"
	    "Pick the given channel from the input. The default is to keep the color of the channel. "
	    "If --gray is used, then the channel will be extracted into graylevel frames instead.");
}


int cmd_channel(int argc, char *argv[])
{
    option_bool_t gray = { false, true };
    const char *channel_names[] = { "r", "g", "b", NULL };
    option_name_t channel = { -1, channel_names };
    option_t options[] = 
    { 
	{ "gray",    'g', OPTION_BOOL, &gray,    false },
	{ "channel", 'c', OPTION_NAME, &channel, true },
	null_option 
    };
    cvl_io_info_t *input_info;    
    cvl_io_info_t *output_info;
    cvl_frame_t *frame;
    bool error;

    cvl_msg_set_command_name("%s", argv[0]);
    if (!cvtool_getopt(argc, argv, options, 0, 0, NULL))
    {
	return 1;
    }

    input_info = cvl_io_info_new();
    output_info = cvl_io_info_new();
    cvl_io_info_link_output_to_input(output_info, input_info);

    error = false;
    while (!cvl_io_eof(stdin, input_info))
    {
	if (!cvl_io_read(stdin, input_info, &frame))
	{
	    error = true;
	    break;
	}
	cvl_frame_to_rgb(frame);
	for (int i = 0; i < cvl_frame_width(frame) * cvl_frame_height(frame); i++)
	{
	    cvl_pixel_t p = cvl_frame_get_i(frame, i);
	    if (gray.value)
	    {
		if (channel.value == 0)
		{
		    p = cvl_pixel_gray_to_rgb(cvl_pixel_rgb_to_r(p));
		}
		else if (channel.value == 1)
		{
		    p = cvl_pixel_gray_to_rgb(cvl_pixel_rgb_to_g(p));
		}
		else
		{
		    p = cvl_pixel_gray_to_rgb(cvl_pixel_rgb_to_b(p));
		}
	    }
	    else
	    {
		if (channel.value == 0)
		{
		    p = cvl_pixel_rgb(cvl_pixel_rgb_to_r(p), 0, 0);
		}
		else if (channel.value == 1)
		{
		    p = cvl_pixel_rgb(0, cvl_pixel_rgb_to_g(p), 0);
		}
		else
		{
		    p = cvl_pixel_rgb(0, 0, cvl_pixel_rgb_to_b(p));
		}
	    }
	    cvl_frame_set_i(frame, i, p);
	}
	if (gray.value)
	{
	    cvl_frame_set_pixel_type(frame, CVL_PIXEL_GRAY);
	}
	if (!cvl_io_write(stdout, output_info, frame))
	{
	    cvl_frame_free(frame);
	    error = true;
	    break;
	}
	cvl_frame_free(frame);
    }

    cvl_io_info_free(input_info);
    cvl_io_info_free(output_info);
    return error ? 1 : 0;
}
