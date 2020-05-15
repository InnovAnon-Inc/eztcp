#if HAVE_CONFIG_H
#include <config.h>
#endif

/*#define _BSD_SOURCE*/
#define _DEFAULT_SOURCE

#include <errno.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <restart.h>

#include <network-client.h>
#include <eztcp-client.h>

/*extern int inet_aton(const char *cp, struct in_addr *inp) ;*/

__attribute__ ((/*leaf, */nonnull (2), nothrow, warn_unused_result))
static int r_connect (fd_t fd, const struct sockaddr *restrict addr, socklen_t addrlen) {
   int retval;
   do retval = connect (fd, addr, addrlen);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

typedef struct {
	eztcp_clientcb_t cb;
	void *restrict args;
} tcp_args_t;

__attribute__ ((nonnull (2, 3), warn_unused_result))
static int my_cb (socket_t s, struct sockaddr_in *restrict si_other,
   void *restrict args) {
   tcp_args_t *restrict my_args = args;
   
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   error_check (r_connect (s, (struct sockaddr *) si_other, (socklen_t) sizeof (*si_other)) == -1) {
	#pragma GCC diagnost pop
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -3;
   }

   error_check (my_args->cb (s, si_other, my_args->args) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -4;
   }
   
   return 0;
}

__attribute__ ((nonnull (2, 3), warn_unused_result))
int eztcp_client (
   uint16_t port, char const addr[],
   eztcp_clientcb_t cb,
   void *restrict cb_args) {
   tcp_args_t args;
   args.cb   = cb;
   args.args = cb_args;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   return network_client (port, addr, SOCK_STREAM, IPPROTO_TCP, my_cb, &args);
	#pragma GCC diagnostic pop
}
