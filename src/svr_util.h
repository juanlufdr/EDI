/*
 * svr_util.h
 *
 *  Created on: 15/01/2014
 *      Author: jarico
 */

#ifndef SVR_UTIL_H_
#define SVR_UTIL_H_

/* Constantes */
#define SVR_PORT           (14935)
#define MAX_LINE           (5000)
#define LISTENQ        (1024)   /*  Backlog for listen()   */


/* Tipos de mensaje que se pueden recibir y su id. asociado*/
/* Longitud incluye caracter de fin de linea */
#define  TYPE_LEN       14

#define  STR_TYPE_USER_SET  "TYPE_USER_SET"
#define  TYPE_USER_SET   1

#define  STR_TYPE_USER_DEL  "TYPE_USER_DEL"
#define  TYPE_USER_DEL   2

#define  STR_TYPE_USER_GET  "TYPE_USER_GET"
#define  TYPE_USER_GET   3

#define  STR_TYPE_CONN_PRF  "TYPE_CONN_PRF"
#define  TYPE_CONN_PRF   4

#define  STR_TYPE_MSGS_PUT  "TYPE_MSGS_PUT"
#define  TYPE_MSGS_PUT   5

#define  STR_TYPE_MSGS_GET  "TYPE_MSGS_GET"
#define  TYPE_MSGS_GET   6

#define  STR_TYPE_DMSG_PUT  "TYPE_DMSG_PUT"
#define  TYPE_DMSG_PUT   7

#define  STR_TYPE_DMSG_GET  "TYPE_DMSG_GET"
#define  TYPE_DMSG_GET   8

#define  TYPE_ERROR     99

extern int  obtenerTipo(char *type);


#define  FIELD_LEN  256


extern  int writevector  (int sockfd, struct iovec *vector, int count);
extern  int readvector   (int sockfd, struct iovec *vector, int count);
extern  int readpacket   (int sockfd, char *buf, int len);
extern  int writepacket  (int sockfd, char *buf, int len) ;
extern  ssize_t rl       (char *msg, char *vptr, size_t maxlen);

extern  ssize_t Readline (int sockd, char *vptr, size_t maxlen);


#endif /* SVR_UTIL_H_ */
