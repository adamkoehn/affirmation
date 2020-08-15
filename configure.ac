#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([affirmation], [0.1.0], [adamkoehn1@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([LIBNOTIFY], [libnotify], [], [AC_MSG_ERROR([libnotify not found])])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 etc/Makefile])
AM_INIT_AUTOMAKE
AC_OUTPUT
