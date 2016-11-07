/*
 * svr_connect.h
 *
 *  Created on: 16/01/2014
 *      Author: Profesores de EDI
 */

#ifndef SVR_CONNECT_H_
#define SVR_CONNECT_H_




#include <string>

#include <iostream>

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/signal.h>
#include <errno.h>




#include<stdio.h>
#include<string.h>    //strlen
#include <cstdlib>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#include "svr_util.h"
#include "svr_user.h"
#include "svr_msg.h"
#include "listapi.h"

using namespace std;

#ifndef EXIT_FAILURE
#define  EXIT_FAILURE  (-1)
#endif
#ifndef EXIT_SUCCESS
#define  EXIT_SUCCESS  ( 0)
#endif

//#define SVR_ADDR      "127.0.0.1"
#define SVR_ADDR      "158.49.227.224"
#define SVR_PORT       (14935)

static char  host[] = "localhost";


/* Esta clase representa una conexion con el servidor */
class SVR_connect {

private:

	int                 send_fd;
	struct sockaddr_in  sendaddr;
	bool                connected;

	bool  connect_rsuex    ();
	void  disconnect_rsuex ();

public:

	SVR_connect();


    bool connected_rsuex ();

	bool send_user  (SVR_user *user);
	void erase_user (const char *id);
	int  receive_users (ListaPI<SVR_user *> * &lsrv_user);

	bool send_msg (SVR_msg *svr_msg);
	int  receive_messages (int from_msg, ListaPI<SVR_msg *> * &lsrv_msgs); // Devuelve cuantos, no el id del ultimo

	bool send_dm_message (SVR_msg *svr_msg);
	int  receive_dm_messages (string user_id, ListaPI<SVR_msg *> * &lsrv_dms); // Devuelve cuantos, no el id del ultimo

	~SVR_connect();
};

#endif /* SVR_CONNECT_H_ */
