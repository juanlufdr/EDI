/*
 * GestorUsuarios.cpp
 *
 *  Created on: 24/03/2014
 *      Author: juanlu
 */

#include "GestorUsuarios.h"

GestorUsuarios::GestorUsuarios() {
	rsuexUsuarios = new ListaPI<Usuario*>();
	seguidos = new Arbol<Usuario*, ComparaPtrUsuarios>();
	svrifaz = new SVR_interfaz();
}

GestorUsuarios::~GestorUsuarios() {
	volcarArbolSeguidos(seguidos, "seguidos.txt");

	borrarListaUsuarios(rsuexUsuarios);

	delete rsuexUsuarios;

	delete seguidos;

}

// operaciones con usuarios

void GestorUsuarios::borrarListaUsuarios(ListaPI<Usuario*> *&lista) {

	Usuario * useraux;
	lista->moverInicio();

	while (!lista->estaVacia()) {
		lista->consultar(useraux);
		delete useraux;
		lista->borrar();
	}
}

void GestorUsuarios::insertarPerfilEnFichero(string id, string nombre,
		string apellidos, string bio, string email) {
	ofstream esc;
	string idaux, nombre_fichero;
	if (id[0] == '@') {
		idaux = id;
		idaux.erase(0, 1);
		nombre_fichero = "Perfil_" + idaux + ".txt";
		esc.open(nombre_fichero.c_str(), ios::trunc);
		if (!esc.fail()) {
			esc << id << endl;
			esc << nombre << endl;
			esc << apellidos << endl;
			esc << bio << endl;
			esc << email << endl;
			esc.close();
		}
	}
}

bool GestorUsuarios::crearPerfil(Usuario *user) {
	string id, nombre, apellidos, bio, email;

	user->obtenerId(id);
	user->obtenerNombre(nombre);
	user->obtenerApellido(apellidos);
	user->obtenerBio(bio);
	user->obtenerEmail(email);

	usuario = user;
	insertarPerfilEnFichero(id, nombre, apellidos, bio, email);

	if (id[0] != '@')
		return false;

	if (svrifaz->insertar_usuario(id, nombre, apellidos, bio, email))
		return true;

	return false;
}

bool GestorUsuarios::buscarUsuario(string id, Usuario *&user) {
	string idaux;
	bool enc = false;

	rsuexUsuarios->moverInicio();

	while (!enc && !rsuexUsuarios->finLista()) {
		rsuexUsuarios->consultar(user);
		user->obtenerId(idaux);
		if (id == idaux)
			enc = true;
		else
			rsuexUsuarios->avanzar();
	}

	if (!enc)
		user = NULL;

	return enc;
}

bool GestorUsuarios::identificarPerfil(string id) {
	ifstream lec;
	Usuario *user;
	string nom_fichero, idaux, nombre, apel, bio, email;
	bool enc = false;

	idaux = id;
	if (idaux[0] == '@')
		idaux.erase(0, 1);
	nom_fichero = "Perfil_" + idaux + ".txt";
	lec.open(nom_fichero.c_str());
	if (!lec.fail()) {
		getline(lec, id);
		getline(lec, nombre);
		getline(lec, apel);
		getline(lec, bio);
		getline(lec, email);
		usuario = new Usuario(id, nombre, apel, bio, email);
		lec.close();
		enc = true;
	}

	if (!buscarUsuario(id, user)) {
		user = new Usuario(id, nombre, apel, bio, email);
		crearPerfil(user);
	}

	lec.open("seguidos.txt");
	if (!lec.fail() && enc) {
		getline(lec, idaux);
		if (idaux.find(id) != -1)
			volcarFicheroEnArbol(lec, seguidos);
		lec.close();
		return true;

	}

	return false;
}

void GestorUsuarios::modificarPerfil(string id) {
	int opcion;
	string dato, nombre, apellidos, bio, email;
	bool salir = false;

	svrifaz->eliminar_usuario(id);
	usuario->obtenerNombre(nombre);
	usuario->obtenerApellido(apellidos);
	usuario->obtenerBio(bio);
	usuario->obtenerEmail(email);

	do {
		pintarMenuModificacion();
		cin >> opcion;
		cin.ignore();
		switch (opcion) {
		case 0:
			salir = true;
			break;
		case 1:
			cout << "Introduce nuevo nombre:" << endl;
			getline(cin, nombre);
			usuario->ponerNombre(nombre);

			break;
		case 2:
			cout << "Introduce nuevos apellidos:" << endl;
			getline(cin, apellidos);
			usuario->ponerApellidos(apellidos);
			break;
		case 3:
			cout << "Introduce nueva biografia:" << endl;
			getline(cin, bio);
			usuario->ponerBio(bio);
			break;
		case 4:
			cout << "Introduce nuevo e-mail:" << endl;
			getline(cin, email);
			usuario->ponerEmail(email);
			break;
		default:
			cout << "Opcion no valida." << endl;
			break;

		}
	} while (!salir);

	usuario->obtenerId(id);
	svrifaz->insertar_usuario(id, nombre, apellidos, bio, email);
	insertarPerfilEnFichero(id, nombre, apellidos, bio, email);
}

bool GestorUsuarios::eliminarPerfil(string id) {
	Usuario *user;
	string nombre_perfil;
	bool enc = false;
	if (buscarUsuario(id, user)) {
		svrifaz->eliminar_usuario(id);
		enc = true;
	}

	if (enc) {
		id.erase(0, 1);
		nombre_perfil = "Perfil_" + id + ".txt";
		remove(nombre_perfil.c_str());
		remove("seguidos.txt");
		while (!seguidos->vacio()) {
			user = seguidos->raiz();
			seguidos->borrar(user);
		}
	}

	return enc;
}

void GestorUsuarios::ListarUsuario() {
	ListaPI<Usuario*> *lAux = new ListaPI<Usuario*>;
	Usuario *usaux;

	svrifaz->obtener_usuarios(lAux);
	borrarListaUsuarios(rsuexUsuarios);
	lAux->moverInicio();

	while (!lAux->estaVacia()) {
		lAux->consultar(usaux);
		insertarOrdenEnLista(usaux);
		lAux->borrar();
	}

	if (rsuexUsuarios->estaVacia())
		cout << "No hay usuarios en el servidor" << endl;

	borrarListaUsuarios(lAux);

	delete lAux;

}

void GestorUsuarios::mostrarListas() {
	Usuario *usaux;

	rsuexUsuarios->moverInicio();

	if (!rsuexUsuarios->estaVacia()) {
		while (!rsuexUsuarios->finLista()) {
			rsuexUsuarios->consultar(usaux);
			usaux->mostrar();
			cout << endl;
			cout << "======================" << endl;
			rsuexUsuarios->avanzar();
		}
	} else
		cout << "No hay usuarios" << endl;
}

void GestorUsuarios::obtenerIdUsuario(string &id) {
	usuario->obtenerId(id);
}

// operaciones con seguidores

bool GestorUsuarios::seguirUsuario(string id) {
	Usuario *aux;

	if (buscarUsuario(id, aux)) {
		seguidos->insertar(aux);
		return true;
	}

	return false;
}

void GestorUsuarios::mostrarSeguidos() {
	if (!seguidos->vacio())
		inOrden(seguidos);
	else
		cout << "No hay ningun usuario seguido" << endl;

}

void GestorUsuarios::dejarSeguir(string id) {
	Usuario *aux;
	buscarUsuario(id, aux);

	if (!seguidos->vacio()) {
		if (seguidos->pertenece(aux)) {
			seguidos->borrar(aux);
			cout << "Usuario borrado" << endl;
		} else
			cout << "No sigues a este usuario" << endl;
	} else
		cout << "No hay usuarios seguidos" << endl;

}

Usuario * GestorUsuarios::buscarSeguidos(
		Arbol<Usuario *, ComparaPtrUsuarios> *abbu, const string &id) {
	Arbol<Usuario*, ComparaPtrUsuarios> *aux;
	Usuario *user = new Usuario(id);
	ComparaPtrUsuarios c;

	if (abbu->vacio()) {
		return NULL;
	} else {

		if (c.operator ()(user, abbu->raiz()) < 0) {
			aux = abbu->hijoIzq();
			if (aux != NULL)
				user = buscarSeguidos(aux, id);
		} else if (c.operator ()(user, abbu->raiz()) > 0) {
			aux = abbu->hijoDer();
			if (aux != NULL)
				user = buscarSeguidos(aux, id);
		} else {
			user = abbu->raiz();
		}
	}

	return user;
}

void GestorUsuarios::mostrarSimilares(const string &id) {
	Arbol<Usuario *, ComparaPtrUsuarios> *aux;

	if (!this->seguidos->vacio()) {
		aux = similares(this->seguidos, id);
		if (aux != NULL) {
			if (!filtroInOrden(aux, id))
				cout << "No hay usuarios que empiezen por ese caracter" << endl;
		} else
			cout << "No hay usuarios que empiezen por " << id << endl;
	} else
		cout << "No existen usuarios" << endl;
}

Arbol<Usuario*, ComparaPtrUsuarios> *GestorUsuarios::obtenerSeguidos() {
	return seguidos;
}

// estadisticas

int GestorUsuarios::contarSeguidos(Arbol<Usuario *, ComparaPtrUsuarios> *abbu) {
	Arbol<Usuario *, ComparaPtrUsuarios> *aux;
	int cont = 0;

	if (!abbu->vacio()) {
		cont++;
		aux = abbu->hijoIzq();
		if (aux != NULL)
			cont = cont + contarSeguidos(aux);
	}

	aux = abbu->hijoDer();

	if (aux != NULL)
		cont = cont + contarSeguidos(aux);

	return cont;
}

int GestorUsuarios::numeroUsuarios() {
	int cont = 0;

	rsuexUsuarios->moverInicio();

	while (!rsuexUsuarios->finLista()) {
		cont++;
		rsuexUsuarios->avanzar();
	}

	return cont;
}

void GestorUsuarios::volcarFicheroEnArbol(ifstream &f,
		Arbol<Usuario*, ComparaPtrUsuarios> *abb) {
	string id;
	Usuario *user;
	ListarUsuario();
	while (!f.eof()) {
		getline(f, id);
		if (buscarUsuario(id, user))
			abb->insertar(user);
	}
}

// metodos privados

void GestorUsuarios::pintarMenuModificacion() {
	cout << "1.- Modificar nombre." << endl;
	cout << "2.- Modificar apellidos." << endl;
	cout << "3.- Modificar biografia." << endl;
	cout << "4.- Modificar e-mail." << endl;
	cout << "0.- Salir." << endl;
}

void GestorUsuarios::insertarOrdenEnLista(Usuario *user) {
	string id, idaux;
	Usuario *usaux;
	bool enc = false;
	user->obtenerId(id);
	rsuexUsuarios->moverInicio();

	while (!enc && !rsuexUsuarios->finLista()) {
		rsuexUsuarios->consultar(usaux);
		usaux->obtenerId(idaux);
		if (idaux > id) {
			enc = true;

		} else
			rsuexUsuarios->avanzar();
	}

	rsuexUsuarios->insertar(user);

}

void GestorUsuarios::inOrden(Arbol<Usuario *, ComparaPtrUsuarios> *abbu) {
	Arbol<Usuario *, ComparaPtrUsuarios> *aux;

	if (!abbu->vacio()) {

		aux = abbu->hijoIzq();
		if (aux != NULL) {
			inOrden(aux);
		}

		abbu->raiz()->mostrar();

		aux = abbu->hijoDer();
		if (aux != NULL) {
			inOrden(aux);
		}

	}
}

bool GestorUsuarios::filtroInOrden(Arbol<Usuario *, ComparaPtrUsuarios> *abbu,
		const string &id) {
	Arbol<Usuario *, ComparaPtrUsuarios> *aux;
	string id_raiz;
	bool enc = false;

	if (!abbu->vacio()) {
		aux = abbu->hijoIzq();
		if (aux != NULL) {
			filtroInOrden(aux, id);
		}
		abbu->raiz()->obtenerId(id_raiz);
		if (empiezaPor(id_raiz, id)) {
			enc = true;
			abbu->raiz()->mostrar();
		}
		aux = abbu->hijoDer();
		if (aux != NULL) {
			filtroInOrden(aux, id);
		}

	}
	return enc;
}

bool GestorUsuarios::empiezaPor(string cad, string subcad) {

	if (cad.find(subcad) == 0)
		return true;
	else
		return false;
}

Arbol<Usuario *, ComparaPtrUsuarios> * GestorUsuarios::similares(
		Arbol<Usuario *, ComparaPtrUsuarios> *abbu, const string &id) {
	Arbol<Usuario*, ComparaPtrUsuarios> *aux;
	Usuario *user;
	string idaux;
	if (abbu->vacio()) {
		return NULL;
	} else {
		user = abbu->raiz();
		user->obtenerId(idaux);
		if (!empiezaPor(idaux, id)) {
			if (id < idaux) {
				aux = abbu->hijoIzq();
				if (aux != NULL)
					aux = similares(aux, id);
			} else if (id > idaux) {
				aux = abbu->hijoDer();
				if (aux != NULL)
					aux = similares(aux, id);
			}
		} else {
			aux = abbu;
		}

	}

	return aux;
}

void GestorUsuarios::volcarArbolSeguidos(
		Arbol<Usuario *, ComparaPtrUsuarios> *abbu, string nombre) {
	ofstream esc;
	string id, inicio;
	esc.open(nombre.c_str(), ios::trunc);
	if (!esc.fail()) {
		usuario->obtenerId(id);
		inicio = "Seguidores de " + id;
		esc << inicio << endl;
		recorrerArbolSeguidos(seguidos, esc);
		esc.close();
	}
}

void GestorUsuarios::recorrerArbolSeguidos(
		Arbol<Usuario *, ComparaPtrUsuarios> *abbu, ofstream &f) {
	Arbol<Usuario*, ComparaPtrUsuarios> *aux;
	//ofstream esc;
	Usuario *user;

	if (!abbu->vacio()) {
		user = abbu->raiz();
		insertarSeguidosFichero(user, f);

		aux = abbu->hijoIzq();
		if (aux != NULL)
			recorrerArbolSeguidos(aux, f);

		aux = abbu->hijoDer();
		if (aux != NULL)
			recorrerArbolSeguidos(aux, f);
	}
}

void GestorUsuarios::insertarSeguidosFichero(Usuario *user, ofstream &f) {
	string id;
	user->obtenerId(id);
	f << id << endl;
}

Arbol<Usuario *, ComparaPtrUsuarios> *GestorUsuarios::obtenerArbolporId(
		Arbol<Usuario *, ComparaPtrUsuarios> *&abb, string id) {
	Arbol<Usuario*, ComparaPtrUsuarios> *aux;
	Usuario *user = new Usuario(id);
	ComparaPtrUsuarios c;

	if (abb->vacio()) {
		return NULL;
	} else {

		if (c.operator ()(user, abb->raiz()) < 0) {
			aux = abb->hijoIzq();
			if (aux != NULL)
				user = buscarSeguidos(aux, id);
		} else if (c.operator ()(user, abb->raiz()) > 0) {
			aux = abb->hijoDer();
			if (aux != NULL)
				user = buscarSeguidos(aux, id);
		} else {
			aux = abb;
		}
	}

	return aux;

}

void GestorUsuarios::obtenerUsuariosArbol(Arbol<Usuario *, ComparaPtrUsuarios> *abb, Usuario *&user1, Usuario *&user2){
Arbol<Usuario*,ComparaPtrUsuarios> *aux;

	if(!abb->vacio()){
		aux = abb->hijoIzq();
		if(aux!=NULL)
		user1 = aux->raiz();

		aux = abb->hijoDer();
		if(aux!=NULL)
		user2 = aux->raiz();


	}
}
