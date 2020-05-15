AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    = eztcp-client-test eztcp-server-test

dist_bin_SCRIPTS  = libeztcp_client_config   libeztcp_server_config
dist_bin_SCRIPTS += eztcp_client_test_config eztcp_server_test_config

lib_LTLIBRARIES += libeztcp-client.la
libeztcp_client_la_LIBADD = @LIBEZTCP_CLIENT_LIBADD@
include_HEADERS += eztcp-client.h

lib_LTLIBRARIES += libeztcp-server.la
libeztcp_server_la_LIBADD = @LIBEZTCP_SERVER_LIBADD@
include_HEADERS += eztcp-server.h

eztcp_client_test_LDADD = @EZTCP_CLIENT_TEST_LIBADD@
EXTRA_eztcp_client_test_DEPENDENCIES = libeztcp-client.la

eztcp_server_test_LDADD = @EZTCP_SERVER_TEST_LIBADD@
EXTRA_eztcp_server_test_DEPENDENCIES = libeztcp-server.la

