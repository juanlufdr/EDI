/*
 * SVR_stub.cpp
 *
 *  Created on: 10/01/2014
 *      Author: Profesores de EDI
 */

#include <iostream>
#include <fstream>

#include "listapi.h"
#include "usuario.h"
#include "mensaje.h"
#include "svr_user.h"
#include "svr_msg.h"

#include "svr_stub.h"

using namespace std;


SVR_stub::SVR_stub() {

	ifstream  f;
	Usuario  *user;
	Mensaje  *msg;
	string    id, nombre, apellidos, bio, email;
	string    remitente, destino, texto;

	id_last_msg = 0;
	id_contador = 0;
	lpi_users   = new ListaPI<Usuario *>();
	lmsgs       = new ListaPI<Mensaje *>();
	ldms        = new ListaPI<Mensaje *>();

	conectar();
	if (conectado()) {
		cout << "CONECTADO al servidor" << endl;
	} else {


		// Leer usuarios
		f.open("svr_users.txt");
		if (f.is_open()) {
			while (!f.eof()) {

				getline(f, id, '#');

				if (!f.eof()) {

					getline(f, nombre, '#');
					getline(f, apellidos, '#');
					getline(f, bio, '#');
					getline(f, email);

					user = new Usuario (id, nombre, apellidos);
					lpi_users->insertar(user);

				}
			}
			f.close();

		}

		// Leer mensajes
		f.open("svr_mensajes.txt");
		if (f.is_open()) {
			while (!f.eof()) {

				getline(f, id, '#');

				if (!f.eof()) {

					getline(f, remitente, '#');
					getline(f, destino, '#');
					getline(f, texto);

					msg = new Mensaje ();

					id_contador = atoi(id.c_str());
					msg->ponerId(id_contador);
					msg->ponerRemite(remitente);
					msg->ponerDestino(destino);
					msg->ponerTexto(texto);

					lmsgs->insertar(msg);
					lmsgs->moverInicio(); // Los almaceno en orden OLD-NEW.

				}
			}
			f.close();

		}

		esta_conectado = false;
		cout << "NO CONECTADO al servidor. Se utilizaran datos locales." << endl;
	}
}


bool  SVR_stub::conectar () {

	connection = new SVR_connect();
	esta_conectado = connection->connected_rsuex();

	return esta_conectado;
}


void  SVR_stub::desconectar () {

	delete connection;
}


bool  SVR_stub::conectado () {

	esta_conectado = connection->connected_rsuex();
	return esta_conectado;
}


bool  SVR_stub::insertar_usuario (string id, string nombre, string apellidos, string bio, string email) {

	if (esta_conectado) {

		SVR_user *user = new SVR_user();

		user->ponerId        (id.c_str());
		user->ponerNombre    (nombre.c_str());
		user->ponerApellidos (apellidos.c_str());
		user->ponerBio       (bio.c_str());
		user->ponerEmail     (email.c_str());

		bool ok = connection->send_user(user);
		delete user;
		return ok;

	} else {

		Usuario *user = new Usuario(id, nombre, apellidos);
		Usuario *svr_user;

		lpi_users->moverInicio();
		while (!lpi_users->finLista()) {
			lpi_users->consultar(svr_user);

			if (user == svr_user) {
				delete user;
				return true;
			}
			lpi_users->avanzar();
		}

		lpi_users->moverInicio();
		lpi_users->insertar(user);

		return true;
	}
}


void  SVR_stub::eliminar_usuario (string id) {

	if (esta_conectado) {

		connection->erase_user(id.c_str());

	} else {

		Usuario *svr_user;
		string   id_actual;

		lpi_users->moverInicio();
		while (!lpi_users->finLista()) {
			lpi_users->consultar(svr_user);

			svr_user->obtenerId(id_actual);
			if (id == id_actual) {
				lpi_users->borrar();
				break;
			}
			else
				lpi_users->avanzar();
		}

		lpi_users->moverInicio();
	}
}


void  SVR_stub::obtener_usuarios (ListaPI<Usuario *> * &lu) {

	Usuario *user, *copia_user;

	if (esta_conectado) {

		ListaPI<SVR_user *> *lsvr_users = new ListaPI<SVR_user *> ();
		SVR_user *svr_user;

		connection->receive_users(lsvr_users);

		lu->moverInicio();

		lsvr_users->moverInicio();
		while (!lsvr_users->finLista()) {
			lsvr_users->consultar(svr_user);

			string id(svr_user->obtenerId());
			string nombre(svr_user->obtenerNombre());
			string apellidos(svr_user->obtenerApellidos());
			string bio (svr_user->obtenerBio());
			string email (svr_user->obtenerEmail());

			user = new Usuario (id, nombre, apellidos, bio, email);
			lu->insertar(user);
			lsvr_users->borrar();
		}

		delete lsvr_users;

	}
	else {
		lu->moverInicio();

		lpi_users->moverInicio();
		while (!lpi_users->finLista()) {
			lpi_users->consultar(user);
			copia_user = new Usuario (user);
			lu->insertar(copia_user);
			lpi_users->avanzar();
		}
	}

}


void  SVR_stub::enviar_mensaje (string remite, string texto) {


	if (esta_conectado) {

		SVR_msg *msg = new SVR_msg();
		msg->ponerRemitente(remite.c_str());
		//msg->ponerOrigen(origen.c_str());
		msg->ponerTexto(texto.c_str());
		connection->send_msg(msg);
		delete msg;

	} else {

		Mensaje *msg = new Mensaje();
		//Fecha    f;

		//f.asignarFecha(12,1,2014);

		msg->ponerId(++id_contador);
		msg->ponerRemite(remite);
		//msg->ponerOrigen(origen);
		msg->ponerTexto(texto);
		//msg->ponerFecha(f);

		lmsgs->moverInicio();
		lmsgs->insertar(msg);

	}
}

void SVR_stub::obtener_mensajes (int from_msg, ListaPI<Mensaje *> * &lm) {

	Mensaje *msg, *copia_msg;
	int id;
	string remitente, destino, texto;
	//Fecha fecha;

	if (esta_conectado) {

		ListaPI<SVR_msg *> *lsvr_msgs = new ListaPI<SVR_msg *> ();
		SVR_msg *svr_msg;

		connection->receive_messages(from_msg, lsvr_msgs);

		lm->moverInicio();

		lsvr_msgs->moverInicio();
		while (!lsvr_msgs->finLista()) {
			lsvr_msgs->consultar(svr_msg);

			id = svr_msg->obtenerId();
			string remitente(svr_msg->obtenerRemitente());
			string destino(svr_msg->obtenerDestino());
			string texto(svr_msg->obtenerTexto());

			msg = new Mensaje (remitente, destino, texto);
			msg->ponerId(id);
			lm->insertar(msg);
			lsvr_msgs->borrar();
		}

		delete lsvr_msgs;

	} else {

		lm->moverInicio();

		lmsgs->moverInicio();
		while (!lmsgs->finLista()) {
			lmsgs->consultar(msg);

			msg->obtenerId(id);
			if (id <= from_msg) break;

			copia_msg = new Mensaje();

			msg->obtenerId(id);
			copia_msg->ponerId(id);

			msg->obtenerRemite(remitente);
			copia_msg->ponerRemite(remitente);

			msg->obtenerDestino(destino);
			copia_msg->ponerDestino(destino);

			msg->obtenerTexto(texto);
			copia_msg->ponerTexto(texto);

			//msg->obtenerFecha(fecha);
			//copia_msg->ponerFecha(fecha);

			lm->moverInicio();
			lm->insertar(copia_msg);
			lmsgs->avanzar();
		}
	}

}


void  SVR_stub::enviar_dm (string remite, string destino, string texto) {


	if (esta_conectado) {
		SVR_msg *dm = new SVR_msg();
		dm->ponerRemitente(remite.c_str());
		dm->ponerDestino(destino.c_str());
		dm->ponerTexto(texto.c_str());
		connection->send_dm_message(dm);
		delete dm;

	} else {

		Mensaje *dm = new Mensaje();
		//Fecha    f;
		string   id;

		//f.asignarFecha(12,1,2014);

		dm->ponerId(++id_contador);
		dm->ponerRemite(remite);
		dm->ponerDestino(destino);
		dm->ponerTexto(texto);
		//dm->ponerFecha(f);

		ldms->moverInicio();
		ldms->insertar(dm);
	}

}


void  SVR_stub::recibir_dms (string user_id, ListaPI<Mensaje *> * &ldm) {

	Mensaje  *msg, *msg_aux;
	string    remitente, destino, texto;
	//Fecha     fecha;
	string    idd;
	int       id;

	if (esta_conectado) {

		ListaPI<SVR_msg *> *lsvr_dms = new ListaPI<SVR_msg *> ();
		SVR_msg *svr_msg;

		connection->receive_dm_messages(user_id, lsvr_dms);

		ldm->moverInicio();

		lsvr_dms->moverInicio();
		while (!lsvr_dms->finLista()) {
			lsvr_dms->consultar(svr_msg);

			id = svr_msg->obtenerId();
			string remitente(svr_msg->obtenerRemitente());
			string destino(svr_msg->obtenerDestino());
			string texto(svr_msg->obtenerTexto());

			msg = new Mensaje (remitente, destino, texto);
			msg->ponerId(id);
			ldm->insertar(msg);

			//msg->mostrar();

			lsvr_dms->borrar();
		}

		delete lsvr_dms;

	} else {

		ldm->moverInicio();

		ldms->moverInicio();
		while (!ldms->finLista()) {
			ldms->consultar(msg);

			msg->obtenerDestino(idd);
			if (idd == user_id) {

				msg_aux = new Mensaje();
				*msg_aux = *msg;

				ldm->insertar(msg_aux);
				ldms->borrar();
			} else
				ldms->avanzar();
		}
	}

}


SVR_stub::~SVR_stub() {

	ofstream   f;
	Usuario   *user;
	Mensaje   *msg;
	string     id, nombre, apellidos, bio, email;
	string     remitente, destino, texto;
	int        idm;


	if (esta_conectado) {
		delete connection;
	} else {

		lpi_users->moverInicio();
		f.open("svr_users.txt", ios::trunc);
		if (!f.is_open()) {
			cout << "ERROR: al copiar datos de USUARIOS al archivo" << endl;
		} else {

			while (!lpi_users->finLista()){

				lpi_users->consultar(user);

				user->obtenerId(id);
				user->obtenerNombre(nombre);
				user->obtenerApellido(apellidos);
				user->obtenerBio(bio);
				user->obtenerEmail(email);

				f << id << '#' << nombre << '#' << apellidos << '#' << bio << '#' << email << endl;

				lpi_users->avanzar();
			}

			f.close();
		}



		lmsgs->moverFinal();
		f.open("svr_mensajes.txt", ios::trunc);
		if (!f.is_open()) {
			cout << "ERROR: al copiar datos de MENSAJES al archivo" << endl;
		} else {

			lmsgs->moverInicio();
			while (!lmsgs->finLista()) {

				lmsgs->consultar(msg);

				msg->obtenerId(idm);
				msg->obtenerRemite(remitente);
				msg->obtenerDestino(destino);
				msg->obtenerTexto(texto);

				f << idm << '#' << remitente << '#' << destino << '#' << texto << endl;

				lmsgs->avanzar();
			}

			f.close();
		}
	}

	// FALTA: Borrar los elementos de las E.D.
	delete lpi_users;

	// FALTA: Borrar los elementos de las E.D.
	delete lmsgs;

	// FALTA: Borrar los elementos de las E.D.
	delete ldms;
}

