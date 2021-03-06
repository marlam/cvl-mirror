bin_PROGRAMS = cvlview

cvlview_SOURCES = main.cpp					\
	err.h err.cpp						\
	conf.h conf.cpp						\
	datafile.h datafile.cpp					\
	cvlview.h cvlview.cpp					\
	dataset_selector.h dataset_selector.cpp			\
	channel_selector.h channel_selector.cpp			\
	scale_selector.h scale_selector.cpp			\
	translation_selector.h translation_selector.cpp		\
	rotation_selector.h rotation_selector.cpp		\
	interpolation_selector.h interpolation_selector.cpp	\
	color_selector.h color_selector.cpp			\
	grid_selector.h grid_selector.cpp			\
	frame_info.h frame_info.cpp				\
	channel_info.h channel_info.cpp				\
	range_selector.h range_selector.cpp			\
	gamma_selector.h gamma_selector.cpp			\
	pseudocolor_selector.h pseudocolor_selector.cpp		\
	heightmap_selector.h heightmap_selector.cpp		\
	view_area.h view_area.cpp				\
	pixel_info.h pixel_info.cpp

if W32
cvlview_SOURCES += icons/appicon.ico
cvlview_LDFLAGS = -mwindows
endif

RESOURCES = icons/appicon.png

EXTRA_DIST = cvlview.qrc $(RESOURCES)	\
	heightmap_quads_vs.glsl		\
	heightmap_strip_vs.glsl		\
	heightmap_fs.glsl

nodist_cvlview_SOURCES = \
	heightmap_quads_vs.glsl.h	\
	heightmap_strip_vs.glsl.h	\
	heightmap_fs.glsl.h		\
	moc_cvlview.cpp			\
	moc_dataset_selector.cpp	\
	moc_channel_selector.cpp	\
	moc_scale_selector.cpp		\
	moc_translation_selector.cpp	\
	moc_rotation_selector.cpp	\
	moc_interpolation_selector.cpp	\
	moc_color_selector.cpp		\
	moc_grid_selector.cpp		\
	moc_frame_info.cpp		\
	moc_channel_info.cpp		\
	moc_range_selector.cpp		\
	moc_gamma_selector.cpp		\
	moc_pseudocolor_selector.cpp	\
	moc_heightmap_selector.cpp	\
	moc_view_area.cpp		\
	moc_pixel_info.cpp		\
	rcc_cvlview.cpp

BUILT_SOURCES = $(nodist_cvlview_SOURCES)

CLEANFILES = $(BUILT_SOURCES)

cvlview_LDADD = \
	$(top_builddir)/gllib/libgl.a		\
	$(top_builddir)/mhlib/libmh.a		\
	$(top_builddir)/gnulib/libgnu.a		\
	$(QTOPENGL_LIBS) $(LIBCVL) $(GLEW_LIBS)

cvlview_CPPFLAGS = \
	-I$(top_builddir)/gnulib -I$(top_srcdir)/gnulib	\
	-I$(top_srcdir)/mhlib				\
	-I$(top_srcdir)/gllib				\
	$(QTOPENGL_CFLAGS) $(GLEW_CFLAGS)

.ico.o:
	echo "IDI_ICON1 ICON DISCARDABLE \"$<\"" | $(WINDRES) -o $@

moc_verbose = $(moc_verbose_$(V))
moc_verbose_ = $(moc_verbose_$(AM_DEFAULT_VERBOSITY))
moc_verbose_0 = @echo "  MOC   " $@;

moc_%.cpp: %.h
	$(moc_verbose)$(MOC) -o $@ $<

rcc_verbose = $(rcc_verbose_$(V))
rcc_verbose_ = $(rcc_verbose_$(AM_DEFAULT_VERBOSITY))
rcc_verbose_0 = @echo "  RCC   " $@;

rcc_%.cpp: %.qrc
	$(rcc_verbose)$(RCC) -o $@ $<

%.glsl.h: %.glsl
	$(AM_V_GEN)DIRNAME="`echo $@ | sed -e s/\\\.glsl\\\.h$$// -e s/[a-zA-Z0-9_-]*$$// -e s/\\\/$$//`"; \
	if [ -n "$$DIRNAME" ]; then mkdir -p "$$DIRNAME"; fi; \
	MACRONAME="`echo $< | sed -e s/^.*\\\/// -e s/\\\.glsl$$// -e s/-/_/g | tr [a-z] [A-Z]`_GLSL_STR"; \
	(echo "#ifndef $$MACRONAME"; \
	 echo "#define $$MACRONAME \\"; \
	 sed -e s/\\\\/\\\\\\\\/g \
	     -e s/\"/\\\\\"/g \
	     -e s/^/\"/ \
	     -e s/$$/\\\\n\"\\\\/ < $<; \
	 echo \"\"; \
	 echo "#endif") > $@
