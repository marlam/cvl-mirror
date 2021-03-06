/*
 * cmd_tonemap.c
 * 
 * This file is part of cvtool, a computer vision tool.
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

#include "config.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include <cvl/cvl.h>

#include "mh.h"


void cmd_tonemap_print_help(void)
{
    mh_msg_fmt_req(
	    "tonemap -m|--method=schlick94 [--brightness=<b>]\n"
	    "tonemap -m|--method=tumblin99 [-l|--max-absolute-luminance=<l>] "
	    "[--display-adaptation-level=<d>] [--max-displayable-contrast=<c>]\n"
	    "tonemap -m|--method=drago03 [-l|--max-absolute-luminance=<l>] [--max-display-luminance=<d>] [--bias=<b>]\n"
	    "tonemap -m|--method=reinhard05 [--intensity=<i>] [--light-adaptation=<l>] [--chromatic-adaptation=<c>]\n"
	    "tonemap -m|--method=ashikhmin02 [-l|--max-absolute-luminance=<l>] [--local-contrast=<c>]\n"
	    "tonemap -m|--method=durand02 [-l|--max-absolute-luminance=<l>] [--sigma-spatial=<ss>] [--sigma-luminance=<sl>] [--base-contrast=<bc>]\n"
	    "tonemap -m|--method=reinhard02 [--key-value=<a>] [--white=<w>] [--sharpness=<s>] [--epsilon=<e>]\n"
	    "\n"
	    "Tone map frames. High dynamic range (HDR) frames are read from standard input, and low dynamic range (LDR) frames "
	    "are written to standard output. For some methods, the results should be gamma corrected.\n"
	    "See the original papers for a description of the parameters.\n"
	    "The default for the maximum absolute luminance is to get it from the file (if specified), or else 150.0.\n"
	    "The default for schlick94 is b=100.0.\n"
	    "The defaults for tumblin99 are d=100.0, c=70.0.\n"
	    "The defaults for drago03 are d=200.0, b=0.85.\n"
	    "The defaults for reinhard05 are i=0.0, l=0.5, c=0.5.\n"
	    "The default for ashikhmin02 is c=0.5.\n"
	    "The defaults for durand02 are ss=0.3, sl=0.4, bc=2.0.\n"
	    "The defaults for reinhard02 are a=0.1, w=1.0, s=10.0, e=0.5.");
}


int cmd_tonemap(int argc, char *argv[])
{
    typedef enum 
    { 
	TM_SCHLICK94, 
	TM_TUMBLIN99, 
	TM_DRAGO03, 
	TM_REINHARD05, 
	TM_ASHIKHMIN02,
	TM_DURAND02,
	TM_REINHARD02
    } method_t;
    const char *method_names[] = 
    { 
	"schlick94", 
	"tumblin99", 
	"drago03", 
	"reinhard05", 
	"ashikhmin02",
	"durand02", 
	"reinhard02", 
	NULL 
    };
    mh_option_name_t method = { -1, method_names };
    mh_option_float_t max_abs_lum = { -1.0f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t schlick94_p = { 100.0f, 1.0f, true, FLT_MAX, true };
    mh_option_float_t tr99_disp_adapt_level = { 100.0f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t tr99_max_contrast = { 70.0f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t drago03_max_disp_lum = { 200.0f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t drago03_bias = { 0.85f, 0.0f, true, 1.0f, true };
    mh_option_float_t reinhard05_intensity = { 0.0f, -8.0f, true, 8.0f, true };
    mh_option_float_t reinhard05_light_adapt = { 0.5f, 0.0f, true, 1.0f, true };
    mh_option_float_t reinhard05_chroma_adapt = { 0.5f, 0.0f, true, 1.0f, true };
    mh_option_float_t ashikhmin02_local_contrast = { 0.5f, 0.0f, true, 10.0f, true };
    mh_option_float_t durand02_sigma_spatial = { 0.3f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t durand02_sigma_luminance = { 0.4f, 0.0f, false, FLT_MAX, true };
    mh_option_float_t durand02_base_contrast = { 3.0f, 1.0f, false, FLT_MAX, true };
    mh_option_float_t reinhard02_key_value = { 0.1f, 0.0f, false, 1.0f, true };
    mh_option_float_t reinhard02_white = { 1.0f, 0.0f, true, 100.0f, false };
    mh_option_float_t reinhard02_sharpness = { 10.0f, 0.0f, true, 100.0f, false };
    mh_option_float_t reinhard02_epsilon = { 0.5f, 0.0f, true, 1.0f, true };
    mh_option_t options[] = 
    {
	{ "method",                    'm', MH_OPTION_NAME,  &method,                     true  },
	{ "max-absolute-luminance",    'l', MH_OPTION_FLOAT, &max_abs_lum,                false },
	{ "brightness",               '\0', MH_OPTION_FLOAT, &schlick94_p,                false },
	{ "display-adaptation-level", '\0', MH_OPTION_FLOAT, &tr99_disp_adapt_level,      false },
	{ "max-displayable-contrast", '\0', MH_OPTION_FLOAT, &tr99_max_contrast,          false },
	{ "max-display-luminance",    '\0', MH_OPTION_FLOAT, &drago03_max_disp_lum,       false },
	{ "bias",                     '\0', MH_OPTION_FLOAT, &drago03_bias,               false },
	{ "intensity",                '\0', MH_OPTION_FLOAT, &reinhard05_intensity,       false },
	{ "light-adaptation",         '\0', MH_OPTION_FLOAT, &reinhard05_light_adapt,     false },
	{ "chromatic-adaptation",     '\0', MH_OPTION_FLOAT, &reinhard05_chroma_adapt,    false },
	{ "local-contrast",           '\0', MH_OPTION_FLOAT, &ashikhmin02_local_contrast, false },
	{ "sigma-spatial",            '\0', MH_OPTION_FLOAT, &durand02_sigma_spatial,     false },
	{ "sigma-luminance" ,         '\0', MH_OPTION_FLOAT, &durand02_sigma_luminance,   false },
	{ "base-contrast",            '\0', MH_OPTION_FLOAT, &durand02_base_contrast,     false },
	{ "key-value",                '\0', MH_OPTION_FLOAT, &reinhard02_key_value,       false },
	{ "white",                    '\0', MH_OPTION_FLOAT, &reinhard02_white,           false },
	{ "sharpness",                '\0', MH_OPTION_FLOAT, &reinhard02_sharpness,       false },
	{ "epsilon",                  '\0', MH_OPTION_FLOAT, &reinhard02_epsilon,         false },
	mh_option_null
    };
    cvl_stream_type_t stream_type;
    cvl_format_t format;
    cvl_frame_t *frame, *tonemapped_frame;
    const char *luminance_tag;
    float tmp_max_abs_lum;

    mh_msg_set_command_name("%s", argv[0]);    
    if (!mh_getopt(argc, argv, options, 0, 0, NULL))
    {
	return 1;
    }

    bool error = false;
    while (!cvl_error())
    {
	cvl_read(stdin, &stream_type, &frame);
	if (!frame)
	    break;

	format = cvl_frame_format(frame);
	cvl_convert_format_inplace(frame, CVL_XYZ);
	if (cvl_frame_format(frame) != CVL_XYZ)
	{
	    mh_msg_err("Input is not an image.");
	    cvl_frame_free(frame);
	    error = true;
	    break;
	}
	luminance_tag = cvl_taglist_get(cvl_frame_taglist(frame), "LUMINANCE");
	cvl_reduce(frame, CVL_REDUCE_MAX, 1, &tmp_max_abs_lum);
	if (tmp_max_abs_lum > 1.001 || (luminance_tag && strcmp(luminance_tag, "ABSOLUTE")))
	{
	    cvl_frame_t *tmpframe = cvl_frame_new_tpl(frame);
	    cvl_luminance_range(tmpframe, frame, 0.0f, tmp_max_abs_lum);
	    cvl_frame_free(frame);
	    frame = tmpframe;
	    if (max_abs_lum.value < 0.0f)
	    {
		max_abs_lum.value = tmp_max_abs_lum;
	    }
	}
	else if (max_abs_lum.value < 0.0f)
	{
	    max_abs_lum.value = 150.0f;
	}
	tonemapped_frame = cvl_frame_new_tpl(frame);
	if (method.value == TM_SCHLICK94)
	{
	    cvl_tonemap_schlick94(tonemapped_frame, frame, schlick94_p.value);
	}
	else if (method.value == TM_TUMBLIN99)
	{
	    cvl_frame_t *tmp = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
		    1, CVL_UNKNOWN, CVL_FLOAT, CVL_TEXTURE);
	    float log_avg_lum = cvl_log_avg_lum(frame, tmp, max_abs_lum.value);
	    cvl_frame_free(tmp);
	    cvl_tonemap_tumblin99(tonemapped_frame, frame, max_abs_lum.value,
		    log_avg_lum, tr99_disp_adapt_level.value, tr99_max_contrast.value);
	}
	else if (method.value == TM_DRAGO03)
	{
	    cvl_tonemap_drago03(tonemapped_frame, frame, max_abs_lum.value, 
		    drago03_bias.value, drago03_max_disp_lum.value);
	}
	else if (method.value == TM_REINHARD05)
	{
  	    float min_lum;
  	    float avg_lum;
 	    float log_avg_lum;
	    float channel_avg[4];
	    cvl_frame_t *tmpframe = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame),
		    3, CVL_RGB, CVL_FLOAT, CVL_TEXTURE);
	    cvl_reduce(frame, CVL_REDUCE_MIN, 1, &min_lum);
	    cvl_reduce(frame, CVL_REDUCE_SUM, 1, &avg_lum);
	    avg_lum /= (float)cvl_frame_size(frame);
	    log_avg_lum = cvl_log_avg_lum(frame, tmpframe, 1.0f);
	    cvl_convert_format(tmpframe, frame);
	    cvl_reduce(tmpframe, CVL_REDUCE_SUM, -1, channel_avg);
	    channel_avg[0] /= (float)cvl_frame_size(frame);
	    channel_avg[1] /= (float)cvl_frame_size(frame);
	    channel_avg[2] /= (float)cvl_frame_size(frame);
            cvl_tonemap_reinhard05(tonemapped_frame, frame,
		    min_lum, avg_lum, log_avg_lum, tmpframe, channel_avg,
		    reinhard05_intensity.value,
		    reinhard05_chroma_adapt.value,
		    reinhard05_light_adapt.value);
	    cvl_frame_free(tmpframe);
	}
	else if (method.value == TM_ASHIKHMIN02)
	{
	    cvl_frame_t *tmpframe = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame),
		    4, CVL_UNKNOWN, CVL_FLOAT, CVL_TEXTURE);
	    float min_abs_lum;
	    cvl_reduce(frame, CVL_REDUCE_MIN, 1, &min_abs_lum);
	    min_abs_lum *= max_abs_lum.value;
	    cvl_tonemap_ashikhmin02(tonemapped_frame, frame,
	    	    min_abs_lum, max_abs_lum.value, tmpframe, ashikhmin02_local_contrast.value);
	    cvl_frame_free(tmpframe);
	}
	else if (method.value == TM_DURAND02)
	{
	    cvl_frame_t *tmp = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame), 
		    4, CVL_UNKNOWN, CVL_FLOAT, CVL_TEXTURE);
	    // Limit kernel size to 9x9 because the graphics card cannot handle more
	    cvl_tonemap_durand02(tonemapped_frame, frame, max_abs_lum.value, tmp,
		    mh_mini(4, cvl_gauss_sigma_to_k(durand02_sigma_spatial.value)),
		    durand02_sigma_spatial.value,
		    durand02_sigma_luminance.value,
		    durand02_base_contrast.value);
	    cvl_frame_free(tmp);
	}
	else if (method.value == TM_REINHARD02)
	{
	    cvl_frame_t *tmpframe = cvl_frame_new(cvl_frame_width(frame), cvl_frame_height(frame),
		    4, CVL_UNKNOWN, CVL_FLOAT, CVL_TEXTURE);
	    float log_avg_lum = cvl_log_avg_lum(frame, tmpframe, 1.0f);
	    cvl_tonemap_reinhard02(tonemapped_frame, frame, tmpframe, log_avg_lum,
		    reinhard02_key_value.value, reinhard02_white.value, 
		    reinhard02_sharpness.value, reinhard02_epsilon.value);
	    cvl_frame_free(tmpframe);
	}
	cvl_frame_free(frame);
	cvl_convert_format_inplace(tonemapped_frame, format);
	cvl_write(stdout, stream_type, tonemapped_frame);
	cvl_frame_free(tonemapped_frame);
    }

    return (cvl_error() || error) ? 1 : 0;
}
