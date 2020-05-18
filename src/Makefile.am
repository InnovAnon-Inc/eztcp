AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libeztcp-client.la
libeztcp_client_la_CPPFLAGS = $(NETWORK_CLIENT_CFLAGS) $(RESTART_CFLAGS)
libeztcp_client_la_LIBADD   = $(NETWORK_CLIENT_LIBS)   $(RESTART_LIBS)
include_HEADERS += eztcp-client.h

lib_LTLIBRARIES += libeztcp-server.la
libeztcp_server_la_CPPFLAGS = $(NETWORK_SERVER_CFLAGS) $(MMALLOC_CFLAGS) $(RESTART_CFLAGS)
libeztcp_server_la_LIBADD   = $(NETWORK_SERVER_LIBS)   $(MMALLOC_LIBS)   $(RESTART_LIBS)
include_HEADERS += eztcp-server.h

bin_PROGRAMS += eztcp-client-test
eztcp_client_test_CPPFLAGS =                $(NETWORK_CFLAGS) $(NETWORK_CLIENT_CFLAGS) $(RESTART_CFLAGS)
eztcp_client_test_LDADD    = -leztcp-client $(NETWORK_LIBS)   $(NETWORK_CLIENT_LIBS)   $(RESTART_LIBS)
EXTRA_eztcp_client_test_DEPENDENCIES = libeztcp-client.la

bin_PROGRAMS += eztcp-server-test
eztcp_server_test_CPPFLAGS =                $(NETWORK_CFLAGS) $(NETWORK_SERVER_CFLAGS) $(MMALLOC_CFLAGS) $(RESTART_CFLAGS)
eztcp_server_test_LDADD    = -leztcp-server $(NETWORK_LIBS)   $(NETWORK_SERVER_LIBS)   $(MMALLOC_LIBS)   $(RESTART_LIBS)
EXTRA_eztcp_server_test_DEPENDENCIES = libeztcp-server.la

