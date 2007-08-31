bin_PROGRAMS = cvlview

cvlview_SOURCES = main.cpp					\
	err.h err.cpp						\
	conf.h conf.cpp						\
	cvlview.h cvlview.cpp					\
	image_info.h image_info.cpp				\
	channel_selector.h channel_selector.cpp			\
	viewpoint_selector.h viewpoint_selector.cpp		\
	interpolation_selector.h interpolation_selector.cpp	\
	channel_info.h channel_info.cpp				\
	range_selector.h range_selector.cpp			\
	gamma_selector.h gamma_selector.cpp			\
	pseudocolor_selector.h pseudocolor_selector.cpp		\
	view_area.h view_area.cpp				\
	pixel_info.h pixel_info.cpp

if W32
cvlview_SOURCES += appicon.ico
endif

nodist_cvlview_SOURCES = \
	moc_cvlview.cpp			\
	moc_image_info.cpp		\
	moc_channel_selector.cpp	\
	moc_viewpoint_selector.cpp	\
	moc_interpolation_selector.cpp	\
	moc_channel_info.cpp		\
	moc_range_selector.cpp		\
	moc_gamma_selector.cpp		\
	moc_pseudocolor_selector.cpp	\
	moc_view_area.cpp		\
	moc_pixel_info.cpp		\
	rcc_cvlview.cpp

BUILT_SOURCES = $(nodist_cvlview_SOURCES)

EXTRA_DIST = appicon.ico appicon.png cvlview.qrc

CLEANFILES = $(BUILT_SOURCES)

cvlview_LDADD = \
	$(top_builddir)/mhlib/libmh.a	\
	$(top_builddir)/gnulib/libgnu.a	\
	$(QT4_LIBS) $(CVL_LIBS)

cvlview_CPPFLAGS = \
	-I$(top_srcdir)/gnulib			\
	-I$(top_srcdir)/mhlib

cvlview_CXXFLAGS = $(QT4_CXXFLAGS)

.ico.o:
	echo "IDI_ICON1 ICON DISCARDABLE \"$<\"" | $(WINDRES) -o $@

moc_%.cpp: %.h
	$(QT4_MOC) -o $@ $<

rcc_%.cpp: %.qrc
	$(QT4_RCC) -o $@ $<

%.glsl.h: %.glsl
	MACRONAME="`echo $< | sed -e s/^.*\\\/// -e s/\\\.glsl$$// -e s/-/_/g | tr [:lower:] [:upper:]`_GLSL_STR"; \
	(echo "#ifndef $$MACRONAME"; \
	 echo "#define $$MACRONAME \\"; \
	 sed -e s/\\\\/\\\\\\\\/g \
	     -e s/\"/\\\\\"/g \
	     -e s/^/\"/ \
	     -e s/$$/\\\\n\"\\\\/ < $<; \
	 echo \"\"; \
	 echo "#endif") > $@