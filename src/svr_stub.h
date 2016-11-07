/*
 * SVR_stub.h
 *
 *  Created on: 10/01/2014
 *      Author: jarico
 */

#ifndef SVR_STUB_H_
#define SVR_STUB_H_

#include "listapi.h"
#include "usuario.h"
#include "mensaje.h"
#include "svr_connect.h"

using namespace std;


class SVR_stub {

private:

	ListaPI<Usuario *> *lpi_users;
	ListaPI<Mensaje *> *lmsgs;
	ListaPI<Mensaje *> *ldms;
	SVR_connect        *connection;     // Conexion con el servidor
	int                 id_last_msg;    // Id. del ultimo mensaje recibido del servidor
	int                 id_contador;    // Numero de mensajes (si actua como servidor, para asignarlo al siguiente)
	bool                esta_conectado; // Esta conectado ?

public:

	 SVR_stub();

	 bool  conectar    ();
	 void  desconectar ();
	 bool  conectado   ();

	 bool  insertar_usuario (string id, string nombre, string apellidos, string bio, string email);
	 void  eliminar_usuario (string id);
	 void  obtener_usuarios (ListaPI<Usuario *> * &lu);

	 void  enviar_mensaje   (string remite, string texto);
	 void  obtener_mensajes (int from_msg, ListaPI<Mensaje *> * &lm);

	 void  enviar_dm        (string remite, string destino, string texto);
	 void  recibir_dms      (string user_id, ListaPI<Mensaje *> * &ldm);

	~SVR_stub();
};

#endif /* SVR_STUB_H_ */
