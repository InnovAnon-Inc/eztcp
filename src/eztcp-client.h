#ifndef _EZTCP_CLIENT_H_
#define _EZTCP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <eztcp.h>

typedef __attribute__ ((nonnull (2), warn_unused_result))
int (*eztcp_clientcb_t) (socket_t, struct sockaddr_in *restrict,
   void *restrict) ;

int eztcp_client (
   uint16_t port, char const addr[],
   eztcp_clientcb_t cb,
   void *restrict cb_args)
__attribute__ ((nonnull (2, 3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _EZTCP_CLIENT_H_ */
