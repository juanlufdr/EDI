/*
 * ui.h
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#ifndef UI_H_
#define UI_H_

#include "GestorUsuarios.h"
#include  "GestorMensajes.h"
//#include "arbol.h"


class UI {

private:

	SVR_interfaz   *svr_ifaz;
	GestorUsuarios *gestorUser;
	GestorMensajes *gestorMsg;

	int  menu     ();
	void ejecutar ();

public:

	 UI();

	 bool conectado ();

	~UI();
};

#endif /* UI_H_ */
