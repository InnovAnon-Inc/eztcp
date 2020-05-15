AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

dist_bin_SCRIPTS = libeztcp_client_config libeztcp_server_config

lib_LTLIBRARIES += libeztcp-client.la
libeztcp_client_la_LIBADD = @LIBEZTCP_CLIENT_LIBADD@
include_HEADERS += eztcp-client.h

lib_LTLIBRARIES += libeztcp-server.la
libeztcp_server_la_LIBADD = @LIBEZTCP_SERVER_LIBADD@
include_HEADERS += eztcp-server.h
