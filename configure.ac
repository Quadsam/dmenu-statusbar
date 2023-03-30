# Autoconf requirements
AC_PREREQ([2.71])

# Information about the package
AC_INIT([dmenu-statusbar], [0.5.4-alpha], [bugs@quadsam.com])
AC_CONFIG_SRCDIR([src/dmenustatus.c])
AC_CONFIG_HEADERS([config.h])
#AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])

# Check for programs
AC_PROG_CC

# Check for libraries
AC_PATH_XTRA
AS_IF([test "$no_x" = "yes"], [AC_MSG_ERROR([Could not find X11])])

# Check for headers
AC_CHECK_HEADERS([unistd.h], [AC_DEFINE([HAVE_UNISTD_H], [1], [Define if unistd.h exists.])], [AC_MSG_ERROR([Missing unistd.h header])])

# Check for types
AC_TYPE_SIZE_T

# Check for structures

# Check for compiler characteristics

# Check for library functions
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset], [AC_DEFINE([HAVE_MEMSET], [1], [Defined if the memset function exists.])])

# Checks for system services
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_FILES([Makefile
				 src/Makefile])
AC_OUTPUT
