/*
 * File: globaldefs.h
 * Name: Mark Erle
 * UID:  mae5
 */

#define SOCK_PATH "socketoomee"       /* name of socket file to create */
#define DOMAIN AF_UNIX                /* protocol family for socket communication */
#define TYPE SOCK_STREAM              /* socket type */
#define PROTOCOL 0                    /* protocol within protocol family (aka domain) */
#define BACKLOG 1                     /* max number of outstanding connections in listen queue */
#define BUFFER_SIZE 140               /* old school max tweet length */
#define FLAGS 0                       /* flags value for send and recv */
