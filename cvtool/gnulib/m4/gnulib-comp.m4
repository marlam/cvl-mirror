# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2010 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects using CVS, this file can be treated like other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([gl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable
  AC_REQUIRE([AC_PROG_RANLIB])
  # Code from module alloca-opt:
  # Code from module arg-nonnull:
  # Code from module binary-io:
  # Code from module c++defs:
  # Code from module c-ctype:
  # Code from module c-strcase:
  # Code from module cloexec:
  # Code from module configmake:
  # Code from module dup2:
  # Code from module environ:
  # Code from module errno:
  # Code from module error:
  # Code from module exitfail:
  # Code from module extensions:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  # Code from module fatal-signal:
  # Code from module fcntl:
  # Code from module fcntl-h:
  # Code from module fd-safer-flag:
  # Code from module float:
  # Code from module getdtablesize:
  # Code from module getopt-gnu:
  # Code from module getopt-posix:
  # Code from module gettext-h:
  # Code from module gperf:
  # Code from module havelib:
  # Code from module iconv:
  # Code from module iconv-h:
  # Code from module iconv_open:
  # Code from module include_next:
  # Code from module inline:
  # Code from module intprops:
  # Code from module inttostr:
  # Code from module localcharset:
  # Code from module memchr:
  # Code from module multiarch:
  # Code from module open:
  # Code from module pipe:
  # Code from module pipe2:
  # Code from module pipe2-safer:
  # Code from module posix_spawn-internal:
  # Code from module posix_spawn_file_actions_addclose:
  # Code from module posix_spawn_file_actions_adddup2:
  # Code from module posix_spawn_file_actions_addopen:
  # Code from module posix_spawn_file_actions_destroy:
  # Code from module posix_spawn_file_actions_init:
  # Code from module posix_spawnattr_destroy:
  # Code from module posix_spawnattr_init:
  # Code from module posix_spawnattr_setflags:
  # Code from module posix_spawnattr_setsigmask:
  # Code from module posix_spawnp:
  # Code from module rawmemchr:
  # Code from module sched:
  # Code from module sigaction:
  # Code from module signal:
  # Code from module sigprocmask:
  # Code from module size_max:
  # Code from module spawn:
  # Code from module stat:
  # Code from module stdbool:
  # Code from module stddef:
  # Code from module stdint:
  # Code from module stdio:
  # Code from module strchrnul:
  # Code from module strerror:
  # Code from module striconv:
  # Code from module string:
  # Code from module strndup:
  # Code from module strnlen:
  # Code from module sys_stat:
  # Code from module sys_wait:
  # Code from module time:
  # Code from module unistd:
  # Code from module unistd-safer:
  # Code from module vasnprintf:
  # Code from module vasprintf:
  # Code from module verify:
  # Code from module wait-process:
  # Code from module warn-on-use:
  # Code from module wchar:
  # Code from module xalloc:
  # Code from module xalloc-die:
  # Code from module xsize:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([gl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='gnulib/m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([gl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gl_LIBSOURCES]))
  m4_pushdef([gl_LIBSOURCES_LIST], [])
  m4_pushdef([gl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='gnulib'
  # Code from module alloca-opt:
  gl_FUNC_ALLOCA
  # Code from module arg-nonnull:
  # Code from module binary-io:
  # Code from module c++defs:
  # Code from module c-ctype:
  # Code from module c-strcase:
  # Code from module cloexec:
  gl_CLOEXEC
  gl_MODULE_INDICATOR_FOR_TESTS([cloexec])
  # Code from module configmake:
  # Code from module dup2:
  gl_FUNC_DUP2
  gl_UNISTD_MODULE_INDICATOR([dup2])
  # Code from module environ:
  gl_ENVIRON
  gl_UNISTD_MODULE_INDICATOR([environ])
  # Code from module errno:
  gl_HEADER_ERRNO_H
  # Code from module error:
  gl_ERROR
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=error:3:c-format])
     AM_][XGETTEXT_OPTION([--flag=error_at_line:5:c-format])])
  # Code from module exitfail:
  # Code from module extensions:
  # Code from module fatal-signal:
  gl_FATAL_SIGNAL
  # Code from module fcntl:
  gl_FUNC_FCNTL
  gl_FCNTL_MODULE_INDICATOR([fcntl])
  # Code from module fcntl-h:
  gl_FCNTL_H
  # Code from module fd-safer-flag:
  gl_MODULE_INDICATOR([fd-safer-flag])
  # Code from module float:
  gl_FLOAT_H
  # Code from module getdtablesize:
  gl_FUNC_GETDTABLESIZE
  gl_UNISTD_MODULE_INDICATOR([getdtablesize])
  # Code from module getopt-gnu:
  gl_FUNC_GETOPT_GNU
  gl_MODULE_INDICATOR_FOR_TESTS([getopt-gnu])
  # Code from module getopt-posix:
  gl_FUNC_GETOPT_POSIX
  # Code from module gettext-h:
  AC_SUBST([LIBINTL])
  AC_SUBST([LTLIBINTL])
  # Code from module gperf:
  # Code from module havelib:
  # Code from module iconv:
  AM_ICONV
  # Code from module iconv-h:
  gl_ICONV_H
  # Code from module iconv_open:
  gl_FUNC_ICONV_OPEN
  # Code from module include_next:
  # Code from module inline:
  gl_INLINE
  # Code from module intprops:
  # Code from module inttostr:
  gl_INTTOSTR
  # Code from module localcharset:
  gl_LOCALCHARSET
  LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(top_builddir)/$gl_source_base\""
  AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])
  # Code from module memchr:
  gl_FUNC_MEMCHR
  gl_STRING_MODULE_INDICATOR([memchr])
  # Code from module multiarch:
  gl_MULTIARCH
  # Code from module open:
  gl_FUNC_OPEN
  gl_FCNTL_MODULE_INDICATOR([open])
  # Code from module pipe:
  gl_PIPE
  # Code from module pipe2:
  gl_FUNC_PIPE2
  gl_UNISTD_MODULE_INDICATOR([pipe2])
  # Code from module pipe2-safer:
  gl_MODULE_INDICATOR([pipe2-safer])
  # Code from module posix_spawn-internal:
  # Code from module posix_spawn_file_actions_addclose:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_addclose])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_addclose])
  # Code from module posix_spawn_file_actions_adddup2:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_adddup2])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_adddup2])
  # Code from module posix_spawn_file_actions_addopen:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_addopen])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_addopen])
  # Code from module posix_spawn_file_actions_destroy:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_destroy])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_destroy])
  # Code from module posix_spawn_file_actions_init:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_init])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_init])
  # Code from module posix_spawnattr_destroy:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_destroy])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_destroy])
  # Code from module posix_spawnattr_init:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_init])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_init])
  # Code from module posix_spawnattr_setflags:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_setflags])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_setflags])
  # Code from module posix_spawnattr_setsigmask:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_setsigmask])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_setsigmask])
  # Code from module posix_spawnp:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnp])
    gl_POSIX_SPAWN_INTERNAL
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnp])
  # Code from module rawmemchr:
  gl_FUNC_RAWMEMCHR
  gl_STRING_MODULE_INDICATOR([rawmemchr])
  # Code from module sched:
  gl_SCHED_H
  # Code from module sigaction:
  gl_SIGACTION
  gl_SIGNAL_MODULE_INDICATOR([sigaction])
  # Code from module signal:
  gl_SIGNAL_H
  # Code from module sigprocmask:
  gl_SIGNALBLOCKING
  gl_SIGNAL_MODULE_INDICATOR([sigprocmask])
  # Code from module size_max:
  gl_SIZE_MAX
  # Code from module spawn:
  gl_SPAWN_H
  # Code from module stat:
  gl_FUNC_STAT
  gl_SYS_STAT_MODULE_INDICATOR([stat])
  # Code from module stdbool:
  AM_STDBOOL_H
  # Code from module stddef:
  gl_STDDEF_H
  # Code from module stdint:
  gl_STDINT_H
  # Code from module stdio:
  gl_STDIO_H
  # Code from module strchrnul:
  gl_FUNC_STRCHRNUL
  gl_STRING_MODULE_INDICATOR([strchrnul])
  # Code from module strerror:
  gl_FUNC_STRERROR
  gl_STRING_MODULE_INDICATOR([strerror])
  # Code from module striconv:
  if test $gl_cond_libtool = false; then
    gl_ltlibdeps="$gl_ltlibdeps $LTLIBICONV"
    gl_libdeps="$gl_libdeps $LIBICONV"
  fi
  # Code from module string:
  gl_HEADER_STRING_H
  # Code from module strndup:
  gl_FUNC_STRNDUP
  gl_STRING_MODULE_INDICATOR([strndup])
  # Code from module strnlen:
  gl_FUNC_STRNLEN
  gl_STRING_MODULE_INDICATOR([strnlen])
  # Code from module sys_stat:
  gl_HEADER_SYS_STAT_H
  AC_PROG_MKDIR_P
  # Code from module sys_wait:
  gl_SYS_WAIT_H
  AC_PROG_MKDIR_P
  # Code from module time:
  gl_HEADER_TIME_H
  # Code from module unistd:
  gl_UNISTD_H
  # Code from module unistd-safer:
  gl_UNISTD_SAFER
  # Code from module vasnprintf:
  gl_FUNC_VASNPRINTF
  # Code from module vasprintf:
  gl_FUNC_VASPRINTF
  gl_STDIO_MODULE_INDICATOR([vasprintf])
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=asprintf:2:c-format])
     AM_][XGETTEXT_OPTION([--flag=vasprintf:2:c-format])])
  # Code from module verify:
  # Code from module wait-process:
  gl_WAIT_PROCESS
  # Code from module warn-on-use:
  # Code from module wchar:
  gl_WCHAR_H
  # Code from module xalloc:
  gl_XALLOC
  # Code from module xalloc-die:
  # Code from module xsize:
  gl_XSIZE
  # End of code from modules
  m4_ifval(gl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gl_LIBSOURCES_DIR])[ ||
      for gl_file in ]gl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gl_LIBSOURCES_DIR])
  m4_popdef([gl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gl_libobjs=
    gl_ltlibobjs=
    if test -n "$gl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gl_libobjs="$gl_libobjs $i.$ac_objext"
        gl_ltlibobjs="$gl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gl_LIBOBJS], [$gl_libobjs])
    AC_SUBST([gl_LTLIBOBJS], [$gl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([gltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gltests_LIBSOURCES]))
  m4_pushdef([gltests_LIBSOURCES_LIST], [])
  m4_pushdef([gltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='tests'
changequote(,)dnl
  gltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([gltests_WITNESS])
  gl_module_indicator_condition=$gltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(gltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]gltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gltests_LIBSOURCES_DIR])
  m4_popdef([gltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gltests_libobjs=
    gltests_ltlibobjs=
    if test -n "$gltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gltests_libobjs="$gltests_libobjs $i.$ac_objext"
        gltests_ltlibobjs="$gltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gltests_LIBOBJS], [$gltests_libobjs])
    AC_SUBST([gltests_LTLIBOBJS], [$gltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_LIBOBJ], [
  AS_LITERAL_IF([$1], [gl_LIBSOURCES([$1.c])])dnl
  gl_LIBOBJS="$gl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gl_LIBSOURCES_DIR], [gnulib])
      m4_append([gl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [gltests_LIBSOURCES([$1.c])])dnl
  gltests_LIBOBJS="$gltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gltests_LIBSOURCES_DIR], [tests])
      m4_append([gltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([gl_FILE_LIST], [
  build-aux/arg-nonnull.h
  build-aux/c++defs.h
  build-aux/config.rpath
  build-aux/warn-on-use.h
  lib/alloca.in.h
  lib/anytostr.c
  lib/asnprintf.c
  lib/asprintf.c
  lib/binary-io.h
  lib/c-ctype.c
  lib/c-ctype.h
  lib/c-strcase.h
  lib/c-strcasecmp.c
  lib/c-strncasecmp.c
  lib/cloexec.c
  lib/cloexec.h
  lib/config.charset
  lib/dup-safer-flag.c
  lib/dup-safer.c
  lib/dup2.c
  lib/errno.in.h
  lib/error.c
  lib/error.h
  lib/exitfail.c
  lib/exitfail.h
  lib/fatal-signal.c
  lib/fatal-signal.h
  lib/fcntl.c
  lib/fcntl.in.h
  lib/fd-safer-flag.c
  lib/fd-safer.c
  lib/float+.h
  lib/float.in.h
  lib/getdtablesize.c
  lib/getopt.c
  lib/getopt.in.h
  lib/getopt1.c
  lib/getopt_int.h
  lib/gettext.h
  lib/iconv.in.h
  lib/iconv_open-aix.gperf
  lib/iconv_open-hpux.gperf
  lib/iconv_open-irix.gperf
  lib/iconv_open-osf.gperf
  lib/iconv_open-solaris.gperf
  lib/iconv_open.c
  lib/imaxtostr.c
  lib/intprops.h
  lib/inttostr.c
  lib/inttostr.h
  lib/localcharset.c
  lib/localcharset.h
  lib/memchr.c
  lib/memchr.valgrind
  lib/offtostr.c
  lib/open.c
  lib/pipe-safer.c
  lib/pipe.c
  lib/pipe.h
  lib/pipe2-safer.c
  lib/pipe2.c
  lib/printf-args.c
  lib/printf-args.h
  lib/printf-parse.c
  lib/printf-parse.h
  lib/rawmemchr.c
  lib/rawmemchr.valgrind
  lib/ref-add.sin
  lib/ref-del.sin
  lib/sched.in.h
  lib/sig-handler.h
  lib/sigaction.c
  lib/signal.in.h
  lib/sigprocmask.c
  lib/size_max.h
  lib/spawn.in.h
  lib/spawn_faction_addclose.c
  lib/spawn_faction_adddup2.c
  lib/spawn_faction_addopen.c
  lib/spawn_faction_destroy.c
  lib/spawn_faction_init.c
  lib/spawn_int.h
  lib/spawnattr_destroy.c
  lib/spawnattr_init.c
  lib/spawnattr_setflags.c
  lib/spawnattr_setsigmask.c
  lib/spawni.c
  lib/spawnp.c
  lib/stat.c
  lib/stdbool.in.h
  lib/stddef.in.h
  lib/stdint.in.h
  lib/stdio-write.c
  lib/stdio.in.h
  lib/strchrnul.c
  lib/strchrnul.valgrind
  lib/strerror.c
  lib/striconv.c
  lib/striconv.h
  lib/string.in.h
  lib/strndup.c
  lib/strnlen.c
  lib/sys_stat.in.h
  lib/sys_wait.in.h
  lib/time.in.h
  lib/uinttostr.c
  lib/umaxtostr.c
  lib/unistd--.h
  lib/unistd-safer.h
  lib/unistd.in.h
  lib/vasnprintf.c
  lib/vasnprintf.h
  lib/vasprintf.c
  lib/verify.h
  lib/w32spawn.h
  lib/wait-process.c
  lib/wait-process.h
  lib/wchar.in.h
  lib/xalloc-die.c
  lib/xalloc.h
  lib/xmalloc.c
  lib/xsize.h
  m4/00gnulib.m4
  m4/alloca.m4
  m4/asm-underscore.m4
  m4/cloexec.m4
  m4/codeset.m4
  m4/dos.m4
  m4/dup2.m4
  m4/environ.m4
  m4/errno_h.m4
  m4/error.m4
  m4/extensions.m4
  m4/fatal-signal.m4
  m4/fcntl-o.m4
  m4/fcntl.m4
  m4/fcntl_h.m4
  m4/float_h.m4
  m4/getdtablesize.m4
  m4/getopt.m4
  m4/glibc21.m4
  m4/gnulib-common.m4
  m4/iconv.m4
  m4/iconv_h.m4
  m4/iconv_open.m4
  m4/include_next.m4
  m4/inline.m4
  m4/intmax_t.m4
  m4/inttostr.m4
  m4/inttypes_h.m4
  m4/lib-ld.m4
  m4/lib-link.m4
  m4/lib-prefix.m4
  m4/localcharset.m4
  m4/longlong.m4
  m4/memchr.m4
  m4/mmap-anon.m4
  m4/mode_t.m4
  m4/multiarch.m4
  m4/open.m4
  m4/pipe.m4
  m4/pipe2.m4
  m4/posix_spawn.m4
  m4/printf.m4
  m4/rawmemchr.m4
  m4/sched_h.m4
  m4/sig_atomic_t.m4
  m4/sigaction.m4
  m4/signal_h.m4
  m4/signalblocking.m4
  m4/size_max.m4
  m4/spawn_h.m4
  m4/stat.m4
  m4/stdbool.m4
  m4/stddef_h.m4
  m4/stdint.m4
  m4/stdint_h.m4
  m4/stdio_h.m4
  m4/strchrnul.m4
  m4/strerror.m4
  m4/string_h.m4
  m4/strndup.m4
  m4/strnlen.m4
  m4/sys_stat_h.m4
  m4/sys_wait_h.m4
  m4/time_h.m4
  m4/unistd-safer.m4
  m4/unistd_h.m4
  m4/vasnprintf.m4
  m4/vasprintf.m4
  m4/wait-process.m4
  m4/warn-on-use.m4
  m4/wchar_h.m4
  m4/wchar_t.m4
  m4/wint_t.m4
  m4/xalloc.m4
  m4/xsize.m4
])
