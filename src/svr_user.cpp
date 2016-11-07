/*
 * svr_user.cpp
 *
 *  Created on: 16/01/2014
 *      Author: jarico
 */

#include <string>
#include <iostream>

#include <cstdlib>
#include <cstring>

#include "svr_user.h"

using namespace std;


SVR_user::SVR_user() {
}

SVR_user::SVR_user(char *id, char *nombre, char *apellidos, char *bio, char *email) {
	strcpy(this->Id,        id);
	strcpy(this->Nombre,    nombre);
	strcpy(this->Apellidos, apellidos);
	strcpy(this->Bio,       bio);
	strcpy(this->Email,     email);
}


void SVR_user::ponerId (const char *id) {
	strcpy(this->Id, id);
}

void SVR_user::ponerNombre (const char *nombre) {
	strcpy(this->Nombre, nombre);
}

void SVR_user::ponerApellidos (const char *apellidos) {
	strcpy(this->Apellidos, apellidos);
}

void SVR_user::ponerBio (const char *bio) {
	strcpy(this->Bio, bio);
}

void SVR_user::ponerEmail (const char *email) {
	strcpy(this->Email, email);
}


char *SVR_user::obtenerId () {
	return &this->Id[0];
}

char *SVR_user::obtenerNombre () {
	return &this->Nombre[0];
}

char *SVR_user::obtenerApellidos () {
	return &this->Apellidos[0];
}

char *SVR_user::obtenerBio () {
	return &this->Bio[0];
}

char *SVR_user::obtenerEmail () {
	return &this->Email[0];
}


int SVR_user::obtenerIdLen () {
	return (strlen(this->Id) + 1);
}

int SVR_user::obtenerNombreLen () {
	return (strlen(this->Nombre) + 1);
}

 int SVR_user::obtenerApellidosLen () {
	return (strlen(this->Apellidos) + 1);
}

 int SVR_user::obtenerBioLen () {
	return (strlen(this->Bio) + 1);
}

 int SVR_user::obtenerEmailLen () {
	return (strlen(this->Email) + 1);
}


void SVR_user::mostrar() {
	cout << this->Id << ": " << this->Nombre << " " << this->Apellidos << endl;
}


bool SVR_user::operator == (const SVR_user &user) {

	if (strcmp(this->Id, user.Id) == 0) {
		return true;
	}
	return false;
}


SVR_user::~SVR_user() {
}
