/*
 * svr_util.cpp
 *
 *  Created on: 15/01/2014
 *      Author: jarico
 */

#include <iostream>
#include <string>

#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "svr_util.h"

using namespace std;




ssize_t Readline(int sockd, char *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {

        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            *buffer++ = c;

            if ( c == '\n' ) {
                break;
            }
            if ( c == '\0' ) {
                break;
            }

        }
        else if ( rc == 0 ) {
            if ( n == 1 ) {
                return 0;
            }
            else {
                break;
            }
        }
        else {
            if ( errno == EINTR ) {
                continue;
            }
            return -1;
        }
    }

    *buffer = 0;
    return n;
}





int readpacket (int sockfd, char *buf, int len) {

    register int nLeft = len;
    register int nData;

    while (nLeft > 0) {

        do {
            nData = read (sockfd, buf, nLeft);


        } while ((nData == -1) && (errno == EINTR));

        if (nData == -1) {
            cerr << "[readpacket] Error reading packet (nData: %d  nLeft: %d  errno: %d)\n" << nData << nLeft << errno << endl;
            return -1;
        }

		if (nData == 0)
			return 0;

        nLeft -= nData;
        buf   += nData;

    }

    return len;
}


int writepacket (int sockfd, char *buf, int len) {

    register int nLeft = len;
    register int nData;

    while (nLeft > 0) {

        do {
            nData = write (sockfd, buf, nLeft);


        } while ((nData == -1) && (errno == EINTR));

        if (nData == -1) {
            cerr << "[writepacket] Error reading packet (nData: %d  nLeft: %d  errno: %d)\n" << nData << nLeft << errno << endl;
            return -1;
        }

		if (nData == 0)
			return 0;

        nLeft -= nData;
        buf   += nData;

    }

    return len;
}





int readvector(int sockfd, struct iovec *vector, int count) {

    int  len = 0;
    int  i;
    register int  sended;
    register int  iov_offset;


    char msg[MAX_LINE - 1];

    len = 0;
    int nleido;
    for (i = 0; i < count; i++) {
        nleido = Readline(sockfd, &msg[0],  (MAX_LINE - 1));
        vector[i].iov_len = nleido;
        memcpy((char *)(vector[i].iov_base), msg, nleido);
    }
    return len;
}


ssize_t rl(char *msg, char *vptr, size_t maxlen) {
    ssize_t n, rc;

    for ( n = 0; n < maxlen; n++ ) {

        *vptr++ = *msg;
        if ( *msg == '\0' ) {
            msg++;
                break;
        }

        msg++;
    }

    return n+1;
}


int writevector(int sockfd, struct iovec *vector, int count) {

    int  len = 0;
    int  i;
    register int  sended;
	register int  iov_offset;

    for (i = 0; i < count; i++)
        len += vector[i].iov_len;
    iov_offset = 0;


    while (len > 0) {

        sended = writev(sockfd, &vector[iov_offset], count - iov_offset);

        len -= sended;

        while (sended >= vector[iov_offset].iov_len) {
            sended -= vector[iov_offset].iov_len;
            iov_offset++;
        }
        //char *v = (char *)vector[iov_offset].iov_base;
        //v += sended;
        //vector[iov_offset].iov_base = v;
        vector[iov_offset].iov_base = (char *)vector[iov_offset].iov_base + sended;
        vector[iov_offset].iov_len  -= sended;


    }

    return len;
}



int  obtenerTipo(char *type) {

	if (strcmp(type, STR_TYPE_USER_SET) == 0)  return TYPE_USER_SET;
	if (strcmp(type, STR_TYPE_USER_DEL) == 0)  return TYPE_USER_DEL;
	if (strcmp(type, STR_TYPE_USER_GET) == 0)  return TYPE_USER_GET;
	if (strcmp(type, STR_TYPE_CONN_PRF) == 0)  return TYPE_CONN_PRF;
	if (strcmp(type, STR_TYPE_MSGS_PUT) == 0)  return TYPE_MSGS_PUT;
	if (strcmp(type, STR_TYPE_MSGS_GET) == 0)  return TYPE_MSGS_GET;
	if (strcmp(type, STR_TYPE_DMSG_PUT) == 0)  return TYPE_DMSG_PUT;
	if (strcmp(type, STR_TYPE_DMSG_GET) == 0)  return TYPE_DMSG_GET;

	return TYPE_ERROR;
}


