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

#include <eztcp-client.h>

/*extern int inet_aton(const char *cp, struct in_addr *inp) ;*/

__attribute__ ((/*leaf, */nonnull (2), nothrow, warn_unused_result))
static int r_connect (fd_t fd, const struct sockaddr *restrict addr, socklen_t addrlen) {
   int retval;
   do retval = connect (fd, addr, addrlen);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (2, 3), warn_unused_result))
int eztcp_client (
   uint16_t port, char const addr[],
   eztcp_clientcb_t cb,
   void *restrict cb_args) {
   struct sockaddr_in si_other;

   const socket_t s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
   error_check (s == -1) return -1;

   bzero (&si_other, sizeof (si_other));
   si_other.sin_family = AF_INET;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   si_other.sin_port = htons (port);
	#pragma GCC diagnostic pop

   error_check (inet_aton (addr, &si_other.sin_addr) == 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -2;
   }

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   error_check (r_connect (s, (struct sockaddr *) &si_other, (socklen_t) sizeof (si_other)) == -1) {
	#pragma GCC diagnost pop
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -3;
   }

   error_check (cb (s, &si_other, cb_args) != 0) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-result"
      r_close (s);
	#pragma GCC diagnostic pop
      return -4;
   }

   error_check (r_close (s) == -1) return -5;

   return 0;
}
