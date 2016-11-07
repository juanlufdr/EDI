/*
 * svr_user.cpp
 *
 *  Created on: 16/01/2014
 *      Author: Profesores de EDI
 */

#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

#include "svr_msg.h"

using namespace std;

SVR_msg::SVR_msg() {

}

SVR_msg::SVR_msg(int id, char *remitente, char *texto) {
	this->Id = id;
	strcpy(this->Remitente, remitente);
	//strcpy(this->Destino, origen);
	strcpy(this->Texto, texto);
	//this->Flags = flags;
}

SVR_msg::SVR_msg(int id, char *remitente, char *destino, char *texto) {
	this->Id = id;
	strcpy(this->Remitente, remitente);
	strcpy(this->Destino, destino);
	strcpy(this->Texto, texto);
	//this->Flags = flags;
}

void SVR_msg::ponerId (int id) {
	this->Id = id;
}

void SVR_msg::ponerRemitente (const char *remitente) {
	strcpy(this->Remitente, remitente);
}

void SVR_msg::ponerDestino (const char *destino) {
	strcpy(this->Destino, destino);
}

/*void SVR_msg::ponerOrigen (const char *origen) {
	strcpy(this->Origen, origen);
}*/

void SVR_msg::ponerTexto (const char *texto) {
	strcpy(this->Texto, texto);
}

/*void SVR_msg::ponerFlags (const int flags) {
	this->Flags |= flags;
}*/


int SVR_msg::obtenerId () {
	return this->Id;
}

char *SVR_msg::obtenerRemitente () {
	return &this->Remitente[0];
}

char *SVR_msg::obtenerDestino () {
	return &this->Destino[0];
}

/*char *SVR_msg::obtenerOrigen () {
	return &this->Origen[0];
}*/

char *SVR_msg::obtenerTexto () {
	return &this->Texto[0];
}

/*int SVR_msg::obtenerFlags () {
	return this->Flags;
}*/


int SVR_msg::obtenerRemitenteLen () {
	return (strlen(this->Remitente) + 1);
}

int SVR_msg::obtenerDestinoLen () {
	return (strlen(this->Destino) + 1);
}

/*int SVR_msg::obtenerOrigenLen () {
	return (strlen(this->Origen) + 1);
}*/

int SVR_msg::obtenerTextoLen () {
	return (strlen(this->Texto) + 1);
}


void SVR_msg::mostrar() {
	cout << this->Id << ": " << this->Remitente << " " << this->Texto /*<< " (" << this->Flags << ")" */<< endl;
}


bool SVR_msg::operator == (const SVR_msg *msg) {

	if (this->Id == msg->Id)
		return true;
	return false;
}



SVR_msg::~SVR_msg() {
	// TODO Auto-generated destructor stub
}
