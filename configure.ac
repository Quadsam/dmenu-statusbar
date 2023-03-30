# Autoconf requirements
AC_PREREQ([2.71])

# Information about the package
AC_INIT([dmenu-statusbar],[0.5.4-alpha],[bugs@quadsam.com])
AC_CONFIG_SRCDIR([src/dmenustatus.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

# Check for programs
AC_PROG_CC

# Check for libraries
AC_MSG_CHECKING([for Xlib])
AC_LINK_IFELSE([AC_LANG_CALL([], [main])],
               [AC_SUBST([X_LIBS], ["-lX11"])
                AC_DEFINE([HAVE_LIBX11], [1], [Define to enable the x11 library])
                AC_MSG_RESULT([yes])],
               [AC_MSG_FAILURE([Unable to find the x11 library on your system.])],
               [-lX11])

# Check for headers

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
