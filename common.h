#ifndef _COMMON_H_
#define _COMMON_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <pthread.h>
#include <utlist.h>

#include "lisp.h"
#include "list/list.h"
#include "patricia/patricia.h"


#define LISP_MAP_REGIST_INTERVAL	10
#define LISP_EID_NAME_LEN		16


struct locator {
	struct sockaddr_storage loc_addr;
	u_int8_t priority, weight, m_priority, m_weight;
};

struct eid {			/* EID Instance */
	int t_flag;		/* -1 is thread is not working, 1 is working */
	pthread_t tid;		/* Pthread ID of this EID instance*/
	int raw_socket;		/* Raw socket for own interface */

	char name[LISP_EID_NAME_LEN];
	char ifname[IFNAMSIZ];
	char authkey[LISP_MAX_KEYLEN];
	list_t * prefix_tuple;
};


#include "maptable.h"

struct lisp {
	int udp_socket;	/* socket for sending encapsulated LISP packet		*/
	int ctl_socket; /* socket for sending control LISP Packet		*/
	int raw_socket; /* socket for sending non encapsulated (native forward)	*/
	
	list_t * eid_tuple;			/* Local EID List		*/
	list_t * loc_tuple;			/* locator address list 	*/
	struct sockaddr_storage mapsrvaddr;	/* Map Server Address		*/
	
	struct maptable * rib;			/* For process caches		*/
	struct maptable * fib;			/* For lookup to forward packet */
};

extern struct lisp lisp;


#endif /* _COMMON_H_ */
