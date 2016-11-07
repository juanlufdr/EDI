/*msg->obtenerRemite(remite);
 * GestorMensajes.cpp
 *
 *  Created on: 06/04/2014
 *      Author: juanlu
 */

#include "GestorMensajes.h"

GestorMensajes::GestorMensajes() {
	publicos = new ListaPI<Mensaje*>();
	DM = new Cola<Mensaje*>();
	svrifaz = new SVR_interfaz();
	idmsg = 0;
}

GestorMensajes::~GestorMensajes() {

	borrarListaMensajes(publicos);

	delete publicos;

	delete DM;
}

// operaciones con mensajes publicos

void GestorMensajes::enviarMensaje(string remitente, string texto) {
	if (texto.length() <= 256)
		svrifaz->enviar_mensaje(remitente, texto);
	else
		cout << "El texto sobrepasa la longitud máxima (256 caracteres)."
				<< endl;
}

bool GestorMensajes::compararTexto(string texto, Mensaje *&msg) {
	string textoaux;
	publicos->consultar(msg);
	msg->obtenerTexto(textoaux);
	if (textoaux.find(texto) != -1)
		return true;
	return false;
}

int GestorMensajes::obtenerIdMsg() {
	return idmsg;

}

void GestorMensajes::obtenerMensajes(int id,
		Arbol<Usuario*, ComparaPtrUsuarios> *abbseguidos, string idUser) {

	ListaPI<Mensaje*> *laux = new ListaPI<Mensaje*>();
	string remitente;
	Mensaje *msgaux;
	Usuario *user;

	svrifaz->obtener_mensajes(id, laux);

	// pone en idmsg el identificador del ultimo mensaje recibido

	laux->moverInicio();
	laux->consultar(msgaux);
	msgaux->obtenerId(idmsg);

	if (!publicos->estaVacia()) {
		publicos->moverFinal();
		publicos->avanzar();
	} else
		publicos->moverInicio();

	while (!laux->finLista()) {

		laux->consultar(msgaux);
		laux->avanzar();
		msgaux->obtenerRemite(remitente);
		user = new Usuario(remitente);
		if (abbseguidos->pertenece(user) || remitente == idUser)
			publicos->insertar(msgaux);
	}

	delete laux;

}

void GestorMensajes::listarMensajes() {
	Mensaje *msg;
	if (!publicos->estaVacia()) {
		publicos->moverFinal();
		publicos->consultar(msg);
		msg->mostrar();
		while (!publicos->enInicio()) {
			publicos->retroceder();
			publicos->consultar(msg);
			msg->mostrar();
		}
	} else
		cout << "ERROR: No hay mensajes publicos en el buzon." << endl;

}

void GestorMensajes::reenviar(int id, string iduser) {
	Mensaje aux;
	string auxtxt, texto, remiteaux;

	if (buscarMensaje(id, aux)) {
		aux.obtenerTexto(auxtxt);
		aux.obtenerRemite(remiteaux);
		texto = "RT :" + remiteaux + " : " + auxtxt;

		svrifaz->enviar_mensaje(iduser, texto);
		cout << "Mensaje reenviado" << endl;
	} else
		cout << "Mensaje no encontrado" << endl;

}

bool GestorMensajes::buscarHastag(string hastag) {
	bool enc = false;
	Mensaje *msg;
	string texto;

	publicos->moverInicio();

	while (!publicos->finLista()) {
		if (compararTexto(hastag, msg)) {
			msg->mostrar();
			enc = true;
		}
		publicos->avanzar();

	}
	return enc;
}

// operaciones con DM

void GestorMensajes::enviarDM(string remite, string destino, string texto) {

	if (texto.length() <= 256)
		svrifaz->enviar_dm(remite, destino, texto);
	else
		cout << "Texto demasiado largo. (Máximo 256 caracteres)" << endl;
}

void GestorMensajes::recibirDM(string id) {
	ListaPI<Mensaje*> *laux = new ListaPI<Mensaje*>();
	Mensaje *msgaux;
	svrifaz->recibir_dms(id, laux);
	while (!DM->vacia())
		DM->desencolar();

	laux->moverInicio();
	while (!laux->finLista()) {
		laux->consultar(msgaux);
		laux->borrar();
		DM->encolar(msgaux);
	}

	borrarListaMensajes(laux);
	delete laux;

}

void GestorMensajes::borrarDM() {
	Mensaje *msgaux;
	DM->primero(msgaux);
	DM->desencolar();
	delete msgaux;
}

void GestorMensajes::listarPrimerDM() {
	Mensaje *msgaux;
	DM->primero(msgaux);
	msgaux->mostrar();
}

bool GestorMensajes::contestarDM(string remitente, string texto) {
	Mensaje *msgaux;
	string destino;
	if (!DM->vacia()) {
		DM->primero(msgaux);
		msgaux->obtenerRemite(destino);
		svrifaz->enviar_dm(remitente, destino, texto);
		DM->desencolar();
		return true;
	}
	delete msgaux;
	return false;
}

void GestorMensajes::volcarColaDM(string nombre, string id) {
	string cabezera;
	ofstream esc;

	if (!DM->vacia()) {
		esc.open(nombre.c_str(), ios::trunc);
		if (!esc.fail()) {
			cabezera = "Buzón de mensajes privados de " + id;
			esc << cabezera << endl;
			recorrerColaDM(esc, id);
			esc.close();

		}
	}
}

void GestorMensajes::recorrerColaDM(ofstream &f, string id) {
	Mensaje *msg;
	string insertar, remitente, texto;
	while (!DM->vacia()) {
		DM->primero(msg);
		msg->obtenerRemite(remitente);
		msg->obtenerTexto(texto);
		insertar = id + "#" + remitente + "#" + texto;
		f << insertar << endl;
		DM->desencolar();
		delete msg;
	}
}

void GestorMensajes::cargarFicheroEnCola(string nombre, string id) {
	ifstream lec;
	string cabezera;
	lec.open(nombre.c_str());
	if (!lec.fail()) {
		getline(lec, cabezera);
		if (cabezera.find(id) != -1)
			recorrerFichero(lec, DM);
		lec.close();
	}
}

// estadisticas

int GestorMensajes::numeroMensajes() {
	int cont = 0;
	while (!publicos->finLista()) {
		cont++;
		publicos->avanzar();
	}
	return cont;
}

int GestorMensajes::numeroRT(string id) {
	int cont = 0;
	Mensaje *msg;
	string texto, remite;
	publicos->moverInicio();
	while (!publicos->finLista()) {
		if (compararTexto("RT", msg)) {
			msg->obtenerRemite(remite);
			if (remite == id)
				cont++;
		}
		publicos->avanzar();
	}
	return cont;
}

int GestorMensajes::numeroidentificador(string id) {
	int cont = 0;
	Mensaje *msg;
	string texto, idRT;
	publicos->moverInicio();
	while (!publicos->finLista()) {
		if (compararTexto(id, msg)) {
			msg->obtenerTexto(texto);
			idRT = "RT :" + id;
			if (texto.find(idRT) == -1)
				cont++;
		}

		publicos->avanzar();
	}
	return cont;
}

// metodos privados

bool GestorMensajes::buscarMensaje(int id, Mensaje &msg) {
	bool enc = false;
	Mensaje *msgaux;
	int idaux;
	publicos->moverInicio();
	while (!publicos->finLista() && !enc) {
		publicos->consultar(msgaux);
		msg = *msgaux;
		msg.obtenerId(idaux);
		if (id == idaux)
			enc = true;
		else
			publicos->avanzar();
	}

	return enc;
}

void GestorMensajes::borrarListaMensajes(ListaPI<Mensaje*> *&lista) {
	Mensaje *msgaux;
	lista->moverInicio();

	while (!lista->estaVacia()) {

		lista->consultar(msgaux);
		delete msgaux;
		lista->borrar();
	}

}

void GestorMensajes::recorrerFichero(ifstream &f, Cola<Mensaje*> *&cola) {
	Mensaje *msg;
	string id, remitente, texto;

	if (cola->vacia()) {
		while (!f.eof()) {
			getline(f, id, '#');
			getline(f, remitente, '#');
			getline(f, texto, '#');
			msg = new Mensaje(remitente, id, texto);
			cola->encolar(msg);
		}
	}
}

void GestorMensajes::volcarEnFicheroPublicos(Usuario *user1, Usuario *user2,
		string nombre_fichero) {
	string id, nombre, apel, bio, email, remite, texto;
	ofstream f;
	int cont = 0;

	Mensaje *msg;
	ListaPI<Mensaje*> *laux = new ListaPI<Mensaje*>;
	f.open(nombre_fichero.c_str());
	if (!f.fail() && (user1!=NULL) || (user2 1= NULL)) {
		user1->obtenerId(id);
		publicos->moverInicio();
		laux->moverInicio();

		while (!publicos->finLista()) {
			publicos->consultar(msg);
			msg->obtenerRemite(remite);
			if (id == remite) {
				laux->insertar(msg);
				cont++;
			}
			publicos->avanzar();

		}
		laux->moverInicio();
		user1->obtenerNombre(nombre);
		user1->obtenerApellido(apel);
		user1->obtenerBio(bio);
		user1->obtenerEmail(email);

		f << id << "#" << nombre << "#" << apel << "#" << bio << "#" << email
				<< "#" << cont << endl;
		while (!laux->finLista()) {
			laux->consultar(msg);
			msg->obtenerTexto(texto);
			f << id << "#" << texto << endl;
			laux->avanzar();
		}
		laux->moverInicio();
		while(!laux->finLista())
			laux->borrar();

		cont = 0;

		publicos->moverInicio();
		laux->moverInicio();
		user2->obtenerId(id);

		while (!publicos->finLista()) {
			publicos->consultar(msg);
			msg->obtenerRemite(remite);
			if (id == remite) {
				laux->insertar(msg);
				cont++;
			}
			publicos->avanzar();

		}
		laux->moverInicio();
		user2->obtenerNombre(nombre);
		user2->obtenerApellido(apel);
		user2->obtenerBio(bio);
		user2->obtenerEmail(email);
		f << id << "#" << nombre << "#" << apel << "#" << bio << "#" << email
				<< "#" << cont << endl;
		while (!laux->finLista()) {
			laux->consultar(msg);
			msg->obtenerTexto(texto);
			f << id << "#" << texto << endl;
			laux->avanzar();
		}
	}
	laux->moverInicio();
	while(!laux->finLista())
		laux->borrar();

	delete laux;

}
