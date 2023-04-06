# Autoconf requirements
AC_PREREQ([2.71])

# Information about the package
AC_INIT([dmenustatus],[0.5.4-alpha],[bugs@quadsam.com])
AC_CONFIG_SRCDIR([src/dmenustatus.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_MAINTAINER_MODE([enable])

# Check for programs
AC_PROG_CC

# Check for headers
AC_MSG_CHECKING([for X11 headers])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <X11/Xlib.h>])],
                  [AC_DEFINE([HAVE_X11_H], [1], [Define if X11 headers are avaliable])
                   AC_MSG_RESULT([yes])],
                  [AC_MSG_FAILURE([no])])

# Check for libraries
AC_MSG_CHECKING([for X11 library])
AC_LINK_IFELSE([AC_LANG_PROGRAM([char XOpenDisplay();], [XOpenDisplay])],
               [AC_SUBST([X_LIBS], ["-lX11"])
                AC_DEFINE([HAVE_XLIB], [1], [Define if the X11 library is avaliable])
                AC_MSG_RESULT([yes])],
               [AC_MSG_FAILURE([no])])

# Check for types
AC_TYPE_SIZE_T

# Check for structures

# Check for compiler characteristics

# Check for library functions
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

# Checks for system services
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
