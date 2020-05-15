#if HAVE_CONFIG_H
#include <config.h>
#endif

#define inline __inline__

#include <errno.h>
#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <restart.h>

#include <mmalloc.h>
#include <network-server.h>
#include <eztcp-server.h>

#define BACKLOG (5)

__attribute__ ((/*leaf, */nonnull (2, 3), nothrow, warn_unused_result))
static int r_accept (fd_t fd, struct sockaddr *restrict addr, socklen_t *restrict addrlen) {
   int retval;
   do retval = accept (fd, addr, addrlen);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

typedef struct {
   eztcp_servercb_t cb;
   void *restrict args;
} tcp_args_t;

__attribute__ ((nonnull (2), warn_unused_result))
static int my_cb (socket_t s, struct sockaddr_in *restrict si_me, void *restrict args) {
   tcp_args_t *restrict my_args = args;
#ifndef NDEBUG
   puts ("my_cb()");
#endif
   
   error_check (listen (s, BACKLOG) == -1) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -1;
   }
#ifndef NDEBUG
   puts ("my_cb(): listening");
#endif
   
   while (true) {
      void *restrict *restrict combined[2];
	  size_t eszs[2];
	  struct sockaddr_in *restrict cli;
      socklen_t *restrict clisz;
      fd_t connfd;

      eszs[0] = sizeof (*cli);
      eszs[1] = sizeof (*clisz);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
      combined[0] = (void *restrict *restrict) &cli;
      combined[1] = (void *restrict *restrict) &clisz;
	#pragma GCC diagnostic pop
      error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -3;
      }
#ifndef NDEBUG
      puts ("my_cb(): mmalloc'd");
#endif

      /*struct sockaddr_in *restrict cli = malloc (sizeof (struct sockaddr_in));*/
      /*socklen_t clisz = sizeof (*cli);*/
      *clisz = sizeof (*cli);
      /*
      error_check (cli == NULL) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -3;
      }
      */
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
      /*connfd = r_accept (s, (struct sockaddr *restrict) cli, &clisz);*/
      connfd = r_accept (s, (struct sockaddr *restrict) cli, clisz);
	#pragma GCC diagnostic pop
      error_check (connfd == -1) {
#ifndef NDEBUG
         puts ("my_cb(): accept failed");
#endif
         mfree2 (cli);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -4;
      }
#ifndef NDEBUG
      puts ("my_cb(): accept");
#endif

      error_check (my_args->cb (connfd, cli, *clisz, my_args->args) != 0) {
         mfree2 (cli);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
         r_close (s);
	#pragma GCC diagnostic pop
         return -5;
      }
#ifndef NDEBUG
      puts ("my_cb(): done");
#endif
   }
   __builtin_unreachable ();
}

__attribute__ ((nonnull (3), warn_unused_result))
int eztcp_server (
   uint16_t port, uint32_t addr,
   eztcp_servercb_t cb, void *restrict cb_args) {
   tcp_args_t args;
   args.cb   = cb;
   args.args = cb_args;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   return network_server (port, addr, SOCK_STREAM, IPPROTO_TCP, my_cb, &args);
	#pragma GCC diagnostic pop
}
