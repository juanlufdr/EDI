/*
 * SVR_interfaz.cpp
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#include <string>

#include "usuario.h"
#include "svr_interfaz.h"
#include "svr_stub.h"

using namespace std;


// Variables est‡ticas. SOLO se puede crear una instancia del cliente.
SVR_stub* SVR_interfaz::svr_stub = new SVR_stub();



SVR_interfaz::SVR_interfaz() {
}

bool  SVR_interfaz::conectado () {
	return svr_stub->conectado();
}


bool  SVR_interfaz::insertar_usuario (string id, string nombre, string apellidos, string bio, string email) {

	return svr_stub->insertar_usuario(id, nombre, apellidos, bio, email);
}

void  SVR_interfaz::eliminar_usuario  (string id) {
	svr_stub->eliminar_usuario(id);
}

void  SVR_interfaz::obtener_usuarios (ListaPI<Usuario *> * &luser) {

	svr_stub->obtener_usuarios(luser);
}


void  SVR_interfaz::enviar_mensaje (string remite, string texto) {

	svr_stub->enviar_mensaje(remite, texto);
}

void SVR_interfaz::obtener_mensajes (int id, ListaPI<Mensaje *> * &lmsg) {

	svr_stub->obtener_mensajes(id, lmsg);
}


void  SVR_interfaz::enviar_dm (string remite, string destino, string texto) {

	svr_stub->enviar_dm(remite, destino, texto);
}

void  SVR_interfaz::recibir_dms (string id, ListaPI<Mensaje *> *&lmsg) {

	svr_stub->recibir_dms(id, lmsg);
}


SVR_interfaz::~SVR_interfaz() {

	delete svr_stub;
}
