# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libeztcp-client.pc src/libeztcp-server.pc src/eztcp-client-test.pc src/eztcp-server-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libeztcp-client.pc.in src/libeztcp-server.pc.in src/eztcp-client-test.pc.in src/eztcp-server-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

