#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <restart.h>

#include <eztcp-server.h>

__attribute__ ((nonnull (2), warn_unused_result))
static int cb (socket_t s, struct sockaddr_in *restrict cli,
   socklen_t clisz, void *restrict args) {
#ifndef NDEBUG
   puts ("cb()");
#endif
   error_check (readwrite (s, s) == -1) return -1;
   mfree2 (cli);
   return 0;
}

int main () {
   uint16_t port = 12345;
   uint32_t addr = 0;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   error_check (eztcp_server (port, addr, cb, NULL) != 0) return EXIT_FAILURE;
	#pragma GCC diagnostic pop
   return EXIT_SUCCESS;
}
