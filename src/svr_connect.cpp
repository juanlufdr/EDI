/*
 * svr_connect.cpp
 *
 *  Created on: 16/01/2014
 *      Author: Profesores de EDI
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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

#include "svr_util.h"
#include "listapi.h"

#include "svr_connect.h"

using namespace std;



SVR_connect::SVR_connect() {

	if (connect_rsuex())
		this->connected = true;
	else
		this->connected = false;

	disconnect_rsuex();

}


bool SVR_connect::connect_rsuex () {

	int    on;
	struct hostent *phost;

	bzero((char *)&sendaddr, sizeof(sendaddr));
	sendaddr.sin_family = AF_INET;

	phost=gethostbyname(host);
	memcpy(&sendaddr.sin_addr, phost->h_addr, phost->h_length);

	//sendaddr.sin_addr.s_addr = atoi(SVR_ADDR);
	sendaddr.sin_addr.s_addr = inet_addr(SVR_ADDR);
	int port = SVR_PORT;
	sendaddr.sin_port = htons(port);

	/* 2. Create the socket to send messages to machine i */
	if (0 > (send_fd = socket(PF_INET, SOCK_STREAM, 0))) {
		cerr << "Server ERROR: creating listening socket" << endl;
		exit(EXIT_FAILURE);
	}

	if (0 > setsockopt(send_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))){
		cerr << "Server ERROR: creating listening socket" << endl;
		exit(EXIT_FAILURE);
	}

	on = 1;
	if (0 > setsockopt(send_fd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on))) {
		cerr << "Server ERROR: creating listening socket" << endl;
		exit(EXIT_FAILURE);
	}

	if (0 > connect(send_fd, (struct sockaddr *)&sendaddr, sizeof(sendaddr))) {
		perror("CONNECT: ");
		connected = false;
	} else {
		connected = true;
	}

	return connected;
}


void SVR_connect::disconnect_rsuex () {

	shutdown(send_fd, SHUT_RDWR);
	close(send_fd);
}


bool SVR_connect::connected_rsuex () {

	return connected;
}


bool SVR_connect::send_user (SVR_user *svr_user) {

	struct iovec user_msg_set [5];
	char msg_type [TYPE_LEN] = STR_TYPE_USER_SET;

	if (! connect_rsuex())
		return false;

	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	user_msg_set[0].iov_base = svr_user->obtenerId();
	user_msg_set[0].iov_len  = svr_user->obtenerIdLen();

	user_msg_set[1].iov_base = svr_user->obtenerNombre();
	user_msg_set[1].iov_len  = svr_user->obtenerNombreLen();

	user_msg_set[2].iov_base = svr_user->obtenerApellidos();
	user_msg_set[2].iov_len  = svr_user->obtenerApellidosLen();

	user_msg_set[3].iov_base = svr_user->obtenerBio();
	user_msg_set[3].iov_len  = svr_user->obtenerBioLen();

	user_msg_set[4].iov_base = svr_user->obtenerEmail();
	user_msg_set[4].iov_len  = svr_user->obtenerEmailLen();

	writevector(send_fd, user_msg_set, 5);

	// Respuesta: 0: OK, 1: Usuario existe y no se ha creado
	char numero[10];
	int num;
	Readline(send_fd, numero, 10);
	num = atoi(numero);

	disconnect_rsuex();

	// ha recibido 1 si EXISTE, y 0 si no. Es decir,
	// devuelve true si se ha insertado, false en otro caso.
	return (num == 1) ? false : true;
}



void SVR_connect::erase_user (const char *id) {

	struct iovec user_msg_set [1];
	char msg_type [TYPE_LEN] = STR_TYPE_USER_DEL;

	if (! connect_rsuex())
		return;

	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	user_msg_set[0].iov_base = (char *)id;
	user_msg_set[0].iov_len  = strlen(id) + 1;

	writevector(send_fd, user_msg_set, 1);

	disconnect_rsuex();
}



int  SVR_connect::receive_users (ListaPI<SVR_user *> * &lsrv_user) {

	char  msg_type   [TYPE_LEN];
	struct iovec r_msg [5];
	SVR_user *user;


	if (! connect_rsuex())
		return -1;

	strcpy(msg_type, STR_TYPE_USER_GET);
	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	char numero[10];
	int num;
	Readline(send_fd, numero, 10);
	num = atoi(numero);

	lsrv_user->moverInicio();

	while (num-- > 0) {

		user = new SVR_user();

		r_msg[0].iov_base = user->obtenerId();
		r_msg[1].iov_base = user->obtenerNombre();
		r_msg[2].iov_base = user->obtenerApellidos();
		r_msg[3].iov_base = user->obtenerBio();
		r_msg[4].iov_base = user->obtenerEmail();

		readvector(send_fd, r_msg, 5);

		lsrv_user->insertar(user);

	}

	disconnect_rsuex();
	return num;
}


bool SVR_connect::send_msg (SVR_msg *svr_msg) {

	char msg_type [TYPE_LEN] = STR_TYPE_MSGS_PUT;
	struct iovec user_msg_set [2];

	if (! connect_rsuex()) return false;

	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	user_msg_set[0].iov_base = svr_msg->obtenerRemitente();
	user_msg_set[0].iov_len  = svr_msg->obtenerRemitenteLen();

	/*
	user_msg_set[1].iov_base = svr_msg->obtenerOrigen();
	user_msg_set[1].iov_len  = svr_msg->obtenerOrigenLen();
	 */

	user_msg_set[1].iov_base = svr_msg->obtenerTexto();
	user_msg_set[1].iov_len  = svr_msg->obtenerTextoLen();

	writevector(send_fd, user_msg_set, 2);

	disconnect_rsuex();
	return true;
}


int  SVR_connect::receive_messages (int from_msg, ListaPI<SVR_msg *> * &lsrv_msgs) {

	char msg_type     [TYPE_LEN];
	char from_msg_str [FIELD_LEN];
	char cuantos_str  [FIELD_LEN];
	char id_str       [FIELD_LEN];
	struct iovec r_msg [3];
	SVR_msg     *msg;
	int          cuantos;
	int          id;


	if (! connect_rsuex())
		return -1;

	strcpy(msg_type, STR_TYPE_MSGS_GET);
	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	sprintf(from_msg_str, "%d", from_msg);
	from_msg_str[strlen(from_msg_str)] = '\0';
	writepacket(send_fd, from_msg_str, strlen(from_msg_str)+1);

	Readline(send_fd, cuantos_str, FIELD_LEN);
	cuantos = atoi(cuantos_str);

	lsrv_msgs->moverInicio();

	int num = cuantos;
	while (num-- > 0) {

		msg = new SVR_msg();

		r_msg[0].iov_base = &id_str[0];
		r_msg[1].iov_base = msg->obtenerRemitente();
		//r_msg[2].iov_base = msg->obtenerDestino();
		r_msg[2].iov_base = msg->obtenerTexto();

		readvector(send_fd, r_msg, 3);

		id = atoi(id_str);
		msg->ponerId(id);

		lsrv_msgs->insertar(msg);
	}

	disconnect_rsuex();
	return cuantos;

}


bool SVR_connect::send_dm_message (SVR_msg *svr_msg) {

	char msg_type [TYPE_LEN] = STR_TYPE_DMSG_PUT;
	struct iovec user_msg_set [3];

	if (! connect_rsuex())
		return false;

	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	user_msg_set[0].iov_base = svr_msg->obtenerRemitente();
	user_msg_set[0].iov_len  = svr_msg->obtenerRemitenteLen();

	user_msg_set[1].iov_base = svr_msg->obtenerDestino();
	user_msg_set[1].iov_len  = svr_msg->obtenerDestinoLen();

	user_msg_set[2].iov_base = svr_msg->obtenerTexto();
	user_msg_set[2].iov_len  = svr_msg->obtenerTextoLen();

	writevector(send_fd, user_msg_set, 3);

	disconnect_rsuex();
	return true;
}


int  SVR_connect::receive_dm_messages (string user_id, ListaPI<SVR_msg *> * &lsrv_dms) {

	SVR_msg         *msg;
	char msg_type    [TYPE_LEN];
	char user_id_str [FIELD_LEN];
	char cuantos_str [FIELD_LEN];
	char id_str      [FIELD_LEN];
	struct iovec r_msg [4];
	int  id;
	int  cuantos;

	if (! connect_rsuex())
		return -1;

	strcpy(msg_type, STR_TYPE_DMSG_GET);
	writepacket(send_fd, &msg_type[0], TYPE_LEN);

	strcpy(user_id_str, user_id.c_str());
	writepacket(send_fd, user_id_str, strlen(user_id_str)+1);

	Readline(send_fd, cuantos_str, FIELD_LEN);
	cuantos = atoi(cuantos_str);

	lsrv_dms->moverInicio();
	int num = cuantos;
	while (num-- > 0) {

		msg = new SVR_msg();

		r_msg[0].iov_base = &id_str[0];
		r_msg[1].iov_base = msg->obtenerRemitente();
		r_msg[2].iov_base = msg->obtenerDestino();
		r_msg[3].iov_base = msg->obtenerTexto();

		readvector(send_fd, r_msg, 4);

		id = atoi(id_str);
		msg->ponerId(id);

		lsrv_dms->insertar(msg);
		lsrv_dms->avanzar();

		msg->mostrar();
	}

	disconnect_rsuex();
	return cuantos;
}


SVR_connect::~SVR_connect() {

}
