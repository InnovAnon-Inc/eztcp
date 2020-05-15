#if HAVE_CONFIG_H
#include <config.h>
#endif

#define inline __inline__

#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <restart.h>

#include <eztcp-server.h>

__attribute__ ((/*leaf, */nonnull (2, 3), nothrow, warn_unused_result))
static int r_accept (fd_t fd, struct sockaddr *restrict addr, socklen_t *restrict addrlen) {
   int retval;
   do retval = accept (fd, addr, addrlen);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (3), warn_unused_result))
int eztcp_server (
   uint16_t port, uint32_t addr,
   eztcp_servercb_t cb, void *restrict cb_args) {
   struct sockaddr_in si_me;

   const socket_t s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
   error_check (s == -1) return -1;

   bzero (&si_me, sizeof (si_me));
   si_me.sin_family = AF_INET;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   si_me.sin_port = htons (port);
	#pragma GCC diagnostic pop
   si_me.sin_addr.s_addr = htonl (addr);

   TODO (type-punned pointers and strict-aliasing ?)
	#pragma GCC diagnostic push
   /*#pragma GCC diagnostic error "-Wstrict-aliasing=3"*/
	#pragma GCC diagnostic error "-Wstrict-aliasing"
   error_check (bind (s, (struct sockaddr *) &si_me, (socklen_t) sizeof (si_me)) == -1) {
	#pragma GCC diagnostic pop
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -2;
   }

   while (true) {
      struct sockaddr_in *restrict cli = malloc (sizeof (struct sockaddr_in));
      socklen_t clisz;
      fd_t connfd;
      error_check (cli == NULL) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -3;
      }
      connfd = r_accept (s, (struct sockaddr *restrict) cli, &clisz);
      error_check (connfd != -1) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         free (cli);
         r_close (s);
	#pragma GCC diagnostic pop
         return -4;
      }

      error_check (cb (connfd, cli, clisz, cb_args) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -5;
      }
   }

   error_check (r_close (s) == -1) return -6;

   return 0;
}
