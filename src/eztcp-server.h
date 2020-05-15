#ifndef _EZTCP_SERVER_H_
#define _EZTCP_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <network.h>

typedef __attribute__ ((warn_unused_result))
int (*eztcp_servercb_t) (socket_t, struct sockaddr_in *restrict cli, socklen_t clisz, void *restrict) ;

int eztcp_server (
   uint16_t port, uint32_t addr,
   eztcp_servercb_t cb, void *restrict cb_args)
__attribute__ ((nonnull (3), warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _EZTCP_SERVER_H_ */
