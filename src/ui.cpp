/*
 * ui.cpp
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#include <iostream>
#include <fstream>

#include "ui.h"

using namespace std;

UI::UI() {

	/* 1. Crear la interfaz con el servidor. Automaticamente
	 *    conecta con el servidor si est� disponible.
	 */

	gestorUser = new GestorUsuarios();
	gestorMsg = new GestorMensajes();
	svr_ifaz = new SVR_interfaz();

	/* Crear los objetos necesarios */

	/* X. Lanzamos la aplicaci�n */
	ejecutar();
}

void UI::ejecutar() {

	int opcion;
	bool salir = false;
	int idmsg;
	string id, nombre, apellidos, bio, email, texto, remitente, destino, hastag;
	Mensaje msg;
	Usuario *user;
	Arbol<Usuario*, ComparaPtrUsuarios> *arbolseguidos;

	// identificacion de usuario

	cout << "Introduce tu identificador : " << endl;
	getline(cin, id);
	if (gestorUser->identificarPerfil(id)) {
		gestorMsg->cargarFicheroEnCola("mensajesprivados.txt", id);
		cout << "Bienvenido " << id << endl;
	} else
		cout << "Usuario no registrado." << endl;

	do {

		opcion = menu();

		switch (opcion) {
		case 0:
			cout << "Estadísticas :" << endl;
			cout << "--------------" << endl;
			arbolseguidos = gestorUser->obtenerSeguidos();

			cout << "Numero de usuarios seguidos : "
					<< gestorUser->contarSeguidos(arbolseguidos) << endl;

			cout << "Numero de mensajes publicos recibidos : "
					<< gestorMsg->numeroMensajes() << endl;

			gestorUser->obtenerIdUsuario(id);
			cout << "Numero de RT : " << gestorMsg->numeroRT(id) << endl;

			cout << "Numero de menciones : "
					<< gestorMsg->numeroidentificador(id) << endl;
			cout << "--------------" << endl;
			cout << endl;
			cout << "Has cerrado sesión. Hasta la próxima. " << endl;
			salir = true;
			break;

		case 1: /* Informe de ESTADO de la conexion */

			if (conectado())
				cout << "Estado: CONECTADO" << endl;
			else
				cout << "Estado: NO CONECTADO. Usando informacion local"
						<< endl;
			break;

		case 2: /* Crear el perfir del usuario */

			cout << "Introduce tu identificador(debe empezar por @) : " << endl;
			getline(cin, id);
			cout << "Introduce tu nombre : " << endl;
			getline(cin, nombre);
			cout << "Introduce tus apellidos : " << endl;
			getline(cin, apellidos);
			cout << "Introduce tu biografia : " << endl;
			getline(cin, bio);
			cout << "Introduce tu e-mail : " << endl;
			getline(cin, email);
			user = new Usuario(id, nombre, apellidos, bio, email);

			if (this->gestorUser->crearPerfil(user))
				cout << "Usuario creado" << endl;
			else
				cout << "Usuario no creado" << endl;

			break;

		case 3: /* Eliminar usuario */
			cout << "Introduce el ID que deseas eliminar : " << endl;
			getline(cin, id);
			if (this->gestorUser->eliminarPerfil(id))
				cout << "Usuario eliminado" << endl;
			else
				cout << "Usuario no eliminado" << endl;
			break;

		case 4: /* Modificar usuario = borrar + crear uno nuevo */
			gestorUser->obtenerIdUsuario(id);
			this->gestorUser->modificarPerfil(id);
			break;

		case 5: /* Obtener Usuarios */

			gestorUser->ListarUsuario();

			break;

		case 6: /* Listar todos los usuarios de RSUEx */

			gestorUser->mostrarListas();

			break;

		case 7: /* Seguir a un usuario */
			cout << "Introduce el id del usuario que quieres seguir : " << endl;
			getline(cin, id);
			if (this->gestorUser->seguirUsuario(id))
				cout << "Usuario seguido " << endl;
			else
				cout << "Usuario NO seguido" << endl;

			break;

		case 8: /* Listado de usuarios seguidos */
			this->gestorUser->mostrarSeguidos();
			break;

		case 9:/* Buscar Usuario Seguido */
			cout << "Introduce el id del usuario que deseas buscar : " << endl;
			getline(cin, id);
			arbolseguidos = gestorUser->obtenerSeguidos();
			user = gestorUser->buscarSeguidos(arbolseguidos, id);
			if (arbolseguidos->pertenece(user))
				user->mostrar();
			else
				cout << "No sigues a ese usuario ." << endl;
			break;

		case 10:/* Buscar Usuarios Similares */
			cout
					<< "Introduce el comienzo del id de los usuarios que deseas mostrar : "
					<< endl;
			getline(cin, id);
			gestorUser->mostrarSimilares(id);
			break;

		case 11: /* Numero de Usuarios Seguidos*/
			arbolseguidos = gestorUser->obtenerSeguidos();
			cout << "Numero de usuarios seguidos : "
					<< gestorUser->contarSeguidos(arbolseguidos) << endl;
			break;

		case 12: /* Dejar de Seguir */
			cout << "Introduce el id del usuario que deseas dejar de seguir :"
					<< endl;
			getline(cin, id);
			gestorUser->dejarSeguir(id);
			break;

		case 13:/* Enviar un mensaje */
			cout << "Introduce el texto : " << endl;
			getline(cin, texto);
			this->gestorMsg->enviarMensaje(id, texto);
			break;

		case 14: /* Recibir lista de mensajes */
			idmsg = this->gestorMsg->obtenerIdMsg();
			arbolseguidos = gestorUser->obtenerSeguidos();
			gestorUser->obtenerIdUsuario(id);
			this->gestorMsg->obtenerMensajes(idmsg, arbolseguidos, id);
			break;

		case 15: /* Listado de mensajes */
			this->gestorMsg->listarMensajes();
			break;

		case 16: /* Reenviar mensaje */
			cout << "Introduce el id del mensaje que quieres reenviar : "
					<< endl;
			cin >> idmsg;
			cin.ignore();
			gestorUser->obtenerIdUsuario(id);
			this->gestorMsg->reenviar(idmsg, id);
			break;

		case 17: /* Buscar por hashtag */
			cout << "Introduce el hastag : " << endl;
			getline(cin, hastag);
			if (this->gestorMsg->buscarHastag(hastag))
				cout << "Hastag encontrado" << endl;
			else
				cout << "Hastag no encontrado" << endl;
			break;

		case 18: /* Enviar un mensaje directo */
			cout << "Introduce el destino : " << endl;
			getline(cin, destino);
			cout << "Introduce el texto : " << endl;
			getline(cin, texto);
			this->gestorUser->obtenerIdUsuario(remitente);
			this->gestorMsg->enviarDM(remitente, destino, texto);
			break;

		case 19: /* Recibir los mensajes directos */
			gestorUser->obtenerIdUsuario(id);
			cout << "Buzón de mensajes privados de " << id << endl;
			this->gestorMsg->recibirDM(id);
			break;

		case 20: /* Borrar el primer mensaje directo */
			this->gestorMsg->borrarDM();
			break;

		case 21: /* Listar el primer mensaje directo recibido */
			this->gestorMsg->listarPrimerDM();
			break;

		case 22: /* Contestar el primer mensaje directo */
			gestorUser->obtenerIdUsuario(id);
			cout << "Introduce el texto : " << endl;
			getline(cin, texto);
			gestorMsg->contestarDM(id, texto);
			break;
		case 23:
			cout << "Introduce el id del seguido :" << endl;
			getline(cin, id);
			Usuario *user1;
			Usuario *user2;
			//ofstream f;

			Arbol<Usuario*, ComparaPtrUsuarios> *abb;
			arbolseguidos = gestorUser->obtenerSeguidos();
			abb = gestorUser->obtenerArbolporId(arbolseguidos, id);

			gestorUser->obtenerUsuariosArbol(abb, user1, user2);

			gestorMsg->volcarEnFicheroPublicos(user1, user2, "msg.txt");

			break;

		default: //borrarListaMensajes(publicos);
			cout << "ERROR en la opcion de menu" << endl;
			break;
		}

	} while (!salir);
}

int UI::menu() {

	int opcion;

	do {
		cout << endl;
		cout << "__________________ MENU PRINCIPAL ________________" << endl
				<< endl;
		cout << "CONEXION" << endl;
		cout << "   1.  Estado de la conexion." << endl;
		cout << "USUARIOS" << endl;
		cout << "   2.  Crear mi perfil." << endl;
		cout << "   3.  Eliminar usuario." << endl;
		cout << "   4.  Modificar usuario." << endl;
		cout << "   5.  Obtener usuarios." << endl;
		cout << "   6.  Listado de usuarios." << endl;
		cout << "SEGUIDOS" << endl;
		cout << "   7.  Seguir." << endl;
		cout << "   8.  Listar seguidos." << endl;
		cout << "   9.	Buscar seguidos." << endl;
		cout << "   10. Buscar seguidos similares." << endl;
		cout << "   11. Contar numero de seguidos" << endl;
		cout << "   12.  Dejar de seguir." << endl;
		cout << "MENSAJES" << endl;
		cout << "   13. Enviar mensaje." << endl;
		cout << "   14. Obtener nuevos mensajes" << endl;
		cout << "   15. Listar mensajes." << endl;
		cout << "   16. Reenviar." << endl;
		cout << "   17. Buscar por hashtag" << endl;
		cout << "MENSAJES DIRECTOS" << endl;
		cout << "   18. Enviar DM." << endl;
		cout << "   19. Recibir DMs." << endl;
		cout << "   20. Borrar DM." << endl;
		cout << "   21. Listar DM." << endl;
		cout << "   22. Contestar DM." << endl;
		cout << "   23. Defensa." << endl;
		cout << "0.  SALIR." << endl << endl;
		cout << "Opcion:  ";
		cin >> opcion;
		cin.ignore();

	} while ((opcion < 0) || (opcion > 23));

	return opcion;
}

bool UI::conectado() {

	return svr_ifaz->conectado();
}

UI::~UI() {
	string id;
	gestorUser->obtenerIdUsuario(id);
	gestorMsg->volcarColaDM("mensajesprivados.txt", id);

	delete svr_ifaz;

	delete gestorUser;

	delete gestorMsg;

}

int main() {
	UI ui;
}

