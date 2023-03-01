AC_PREREQ([2.71])
AC_INIT([dmenu-statusbar], [0.5.2-alpha], [bugs@quadsam.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PATH_XTRA
AS_IF([test "$no_x" = "yes"], [AC_MSG_ERROR([Could not find X11])])
AC_CHECK_HEADERS([unistd.h])
AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])
AC_CONFIG_FILES([Makefile
				 src/Makefile])
AC_OUTPUT
