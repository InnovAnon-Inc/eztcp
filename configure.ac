AC_INIT([libeztcp], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_SUBDIRS([glitter restart])

AC_CHECK_HEADERS([stdint.h strings.h unistd.h])
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h sys/types.h sys/socket.h])
AC_CHECK_HEADERS([restart.h glitter.h])

AC_CHECK_LIB([restart],[r_close])

#srcdir = @srcdir@
LIBEZTCP_CLIENT_LIBADD="`PATH=src:$PATH libeztcp_client_config --libs`"
AC_SUBST(LIBEZTCP_CLIENT_LIBADD)

LIBEZTCP_SERVER_LIBADD="`PATH=src:$PATH libeztcp_server_config --libs`"
AC_SUBST(LIBEZTCP_SERVER_LIBADD)

EZTCP_CLIENT_TEST_LIBADD="`PATH=src:$PATH eztcp_client_test_config --libs`"
AC_SUBST(EZTCP_CLIENT_TEST_LIBADD)

EZTCP_SERVER_TEST_LIBADD="`PATH=src:$PATH eztcp_server_test_config --libs`"
AC_SUBST(EZTCP_SERVER_TEST_LIBADD)

INNOVANON_WARNINGS([])

AC_OUTPUT
