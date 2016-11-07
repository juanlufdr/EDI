/*
 * mensaje.cpp
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#include <iostream>

#include "mensaje.h"

using namespace std;

static int cont = 0;

Mensaje::Mensaje() {
	id = ++cont;
	this->remitente="";
	this->destino="";
	this->texto="";
}
Mensaje::Mensaje(string remitente, string destino, string texto){
	this->id = ++cont;
	this->remitente = remitente;
	this->destino = destino;
	this->texto = texto;
}

void Mensaje::ponerId(const int id) {
	this->id = id;
}

void Mensaje::ponerRemite(string remitente) {
	this->remitente = remitente;
}

void Mensaje::ponerDestino(string destino) {
	this->destino = destino;
}

void Mensaje::ponerTexto(string texto) {
	this->texto = texto;
}

void Mensaje::obtenerId(int &id) {
	id = this->id;
}

void Mensaje::obtenerRemite(string & remitente) {
	remitente = this->remitente;
}

void Mensaje::obtenerDestino(string & destino) {
	destino = this->destino;
}

void Mensaje::obtenerTexto(string & texto) {
	texto = this->texto;
}

void Mensaje::mostrar() {
	cout << this->id << "->" << this->remitente << "->" << this->destino
			<< " : " << this->texto << endl;
}

bool Mensaje::operator <(const Mensaje * msg) {
	return (id < msg->id);
}

bool Mensaje::operator >(const Mensaje * msg) {
	return (id > msg->id);
}

bool Mensaje::operator ==(const Mensaje * msg) {
	return (id == msg->id);
}

Mensaje::~Mensaje() {
}
