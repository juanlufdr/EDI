/*
 * svr_msg.h
 *
 *  Created on: 16/01/2014
 *      Author: Profesores de EDI
 */

#ifndef SVR_MSG_H_
#define SVR_MSG_H_

#include "svr_util.h"


/*const int FLAG_ORIGINAL   = 0x0001;
const int FLAG_REENVIADO  = 0x0002;
const int FLAG_RESPONDIDO = 0x0004;
*/

class SVR_msg {

private:

	int   Id;
	char  Remitente [FIELD_LEN];
	char  Destino   [FIELD_LEN];
	//char  Origen    [FIELD_LEN];
	char  Texto     [FIELD_LEN];
	//int   Flags;

public:

	 SVR_msg();
	 SVR_msg(int id, char *remite, char *texto);
	 SVR_msg(int id, char *remite, char *destino, char *texto);

	 void  ponerId        (int id);
	 void  ponerRemitente (const char *remitente);
	 void  ponerDestino   (const char *destino);
	 //void  ponerOrigen    (const char *origen);
	 void  ponerTexto     (const char *texto);
	 //void  ponerFlags     (const int flags);

	 int   obtenerId        ();
	 char *obtenerRemitente ();
	 char *obtenerDestino   ();
	 //char *obtenerOrigen    ();
	 char *obtenerTexto     ();
	 //int   obtenerFlags     ();

	 int   obtenerRemitenteLen ();
	 int   obtenerDestinoLen   ();
	 //int   obtenerOrigenLen    ();
	 int   obtenerTextoLen     ();

	 void  mostrar();

	 bool  operator == (const SVR_msg *msg);


	~SVR_msg();
};

#endif /* SVR_USER_H_ */
