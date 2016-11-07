/*
 * Usuario.cpp
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#include <iostream>

#include "usuario.h"

using namespace std;

Usuario::Usuario() {
	this->idUser = "";
	this->nombre = "";
	this->apellidos = "";
	this->bio = "";
	this->email = "";
}

Usuario::Usuario(string id){
	this->idUser = id;
}

Usuario::Usuario(string id, string nombre, string apellidos) {
	this->idUser = id;
	this->nombre = nombre;
	this->apellidos = apellidos;
}

Usuario::Usuario(string id, string nombre, string apellidos, string bio,
		string email) {
	this->idUser = id;
	this->nombre = nombre;
	this->apellidos = apellidos;
	this->bio = bio;
	this->email = email;
}

Usuario::Usuario(Usuario * &user) {
	this->idUser = user->idUser;
	this->nombre = user->nombre;
	this->apellidos = user->apellidos;
	this->bio = user->bio;
	this->email = user->email;

}

void Usuario::ponerId(const string id) {
	this->idUser = id;
}

void Usuario::ponerNombre(const string nombre) {
	this->nombre = nombre;
}

void Usuario::ponerApellidos(const string apellidos) {
	this->apellidos = apellidos;
}

void Usuario::ponerBio(const string bio) {
	this->bio = bio;

}
void Usuario::ponerEmail(const string email) {
	this->email = email;
}

void Usuario::obtenerId(string &id) {
	id = this->idUser;
}

void Usuario::obtenerNombre(string & nombre) {
	nombre = this->nombre;
}

void Usuario::obtenerApellido(string & apellidos) {
	apellidos = this->apellidos;
}

void Usuario::obtenerBio(string &bio) {
	bio = this->bio;
}

void Usuario::obtenerEmail(string &email) {
	email = this->email;
}

void Usuario::mostrar() {
	cout << "ID: " << idUser << "// Nombre : " << nombre << "// Apellidos: "
			<< apellidos << "// Biografia : " << bio << " // E-mail: " << email
			<< endl;
}

bool Usuario::operator ==(const Usuario &user) {

	if (user.idUser == idUser)
		return true;
	return false;
}

void Usuario::operator =(const Usuario *&user) {

	this->idUser = user->idUser;
	this->nombre = user->nombre;
	this->apellidos = user->apellidos;
	this->bio = user->bio;
	this->email = user->email;

}

bool Usuario::operator !=(const Usuario &user) {

	if (user.idUser != idUser)
		return true;
	return false;
}

bool Usuario::operator <(const Usuario &user) {

	cout << "Comparando <: " << idUser << " con " << user.idUser << endl;
	if (idUser < user.idUser)
		return true;
	return false;
}

bool Usuario::operator >(const Usuario &user) {

	if (idUser > user.idUser)
		return true;
	return false;
}

bool Usuario::operator ()(const Usuario *user1, const Usuario *user2) {

	cout << "Comparando* <: " << user1->idUser << " con " << user2->idUser
			<< endl;
	if (user1->idUser < user2->idUser)
		return true;
	return false;
}

bool Usuario::operator ()(const Usuario &user1, const Usuario &user2) {

	cout << "Comparando& <: " << user1.idUser << " con " << user2.idUser
			<< endl;
	if (user1.idUser < user2.idUser)
		return true;
	return false;
}
Usuario::~Usuario() {

}
