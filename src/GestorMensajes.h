/*
 * GestorMensajes.h
 *
 *  Created on: 06/04/2014
 *      Author: Juan Luis Fragoso del Rey
 *      Descripcion : Gestiona todo lo relacionado con los mensajes publicos y privados
 */
#include <iostream>
#include "mensaje.h"
#include "listapi.h"
#include "GestorUsuarios.h"
#include "svr_interfaz.h"
#include <fstream>
using namespace std;

#ifndef GESTORMENSAJES_H_
#define GESTORMENSAJES_H_

class GestorMensajes {
private:
	SVR_interfaz *svrifaz; // objeto del servidor que nos permite obtener datos del mismo
	//GestorUsuarios usuarios; // objeto de tipo gestorusuarios utilizado para obtener informacion de los usuarios registrados en la plataforma
	ListaPI<Mensaje*> *publicos; //Puntero a ListaPI de punteros a mensajes que almacena los mensajes publicos enviados por los usarios seguidos
	Cola<Mensaje*> *DM; // Puntero a Cola de punteros a mensajes que almacena los mensajes privados enviados al usuario que maneja la aplicacion
	int idmsg;

	/*
	 * DESC: Busca un mensaje en la lista de mensajes publicos
	 * PRE: lista publicos no vacia
	 * POST: true si encuentra el mensaje, false en caso contrario
	 * PARAM: id de tipo entero, msg de tipo Mensaje de entrada/salida
	 * COMP: O(n)
	 */

	bool buscarMensaje(int id, Mensaje &msg);

	/*
	 * DESC: Borra los mensajes almacenados en la lista
	 * PRE: lista no vacia
	 * POST: la lista queda sin mensajes en sus nodos
	 * PARAM: puntero a lista de entrada/salida y de tipo ListaPI<Mensaje*>
	 * COMP: O(n)
	 */

	void borrarListaMensajes(ListaPI<Mensaje*> *&lista);

	/*
	 * DESC: Recorre el fichero e inserta los datos en la cola
	 * PRE: fichero abierto correctamente y no vacio
	 * POST: cola contiene los mensajes almacenados en la cola
	 * PARAM: flujo f de entrada/salida de tipo ifstream, puntero a cola de entrada/salida de tipo Cola<Mensaje*>
	 * COMP: O(n)
	 */

	void recorrerFichero(ifstream &f, Cola<Mensaje*> *&cola);

public:

	/*
	 * DESC: Crea la instancia de la clase GestorMensajes
	 * PRE: ---
	 * POST: La instancia queda creada correctamente
	 * PARAM: ---
	 * COMP: O(1)
	 */

	GestorMensajes();

	/*
	 * DESC: Elimina la instancia de GestorMensajes
	 * PRE: La instancia debe estar creada correctamente
	 * POST: La instancia queda eliminada de memoria
	 * PARAM: ---
	 * COMP: O(n)
	 */

	~GestorMensajes();

	// operaciones con mensajes publicos

	/*
	 * DESC: Envia un mensaje al servidor
	 * PRE: La instancia debe estar creada correctamente y el texto <= 256 caracteres
	 * POST: Envia al servidor un mensaje que contiene el texto y el remitente pasado como parametros
	 * PARAM: remitente y texto de tipo string
	 * COMP: O(1)
	 */

	void enviarMensaje(string remitente, string texto);

	/*
	 * DESC: Comprueba si el texto se encuentra en el mensaje
	 * PRE: publicos no vacio
	 * POST: true si se encuentra el texto, false en caso contrario
	 * PARAM: texto de tipo string, puntero msg de entrada/salida de tipo Mensaje
	 * COMP: O(1)
	 */

	bool compararTexto(string texto, Mensaje *&msg);

	/*
	 * DESC: Devuelve el id del ultimo mensaje recibido en el servidor
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve el id del ultimo mensaje recibido del servidor. Si esta vacia devuelve 0
	 * PARAM: ---
	 * COMP: O(1)
	 */

	int obtenerIdMsg();

	/*
	 * DESC: Almacena los mensajes publicos de los usuarios seguidos y los del usuario en la lista publicos
	 * PRE: La instancia debe estar creada correctamente y abbseguidos no vacio
	 * POST: publicos contiene los mensajes del los usuarios seguidos y los del usuario
	 * PARAM: id de tipo entero, puntero a abbseguidos de tipo Arbol<Usuario*, ComparaPtrUsuarios>, idUser de tipo string
	 * COMP: O(n)
	 */

	void obtenerMensajes(int id,
			Arbol<Usuario*, ComparaPtrUsuarios> *abbseguidos, string idUSer);

	/*
	 * DESC: Muestra por pantalla los mensajes almacenados en la lista publicos
	 * PRE: la lista publicos no debe estar vacia
	 * POST:  Muestra por pantalla los mensajes almacenados en la lista publicos
	 * PARAM: ---
	 * COMP: O(n)
	 */

	void listarMensajes();

	/*
	 * DESC: Reenvia al servidor un mensaje seleccionado por el usuario
	 * PRE: lista publicos no debe estar vacia
	 * POST: se envia al servidor un mensaje de la lista publicos con el id del usuario como remitente
	 * PARAM: id de tipo entero, iduser de tipo string
	 * COMP: O(n)
	 */

	void reenviar(int id, string iduser);

	/*
	 * DESC: Busca en la lista de mensajes publicos los mensajes que contengan el string pasado como parametro
	 * PRE: La instancia debe estar creada correctamente y la lista publicos no debe estar vacia
	 * POST: Devuelve TRUE si encuentra el string pasado como parametro lo muestra por pantalla. False en caso contrario
	 * PARAM: hastag de tipo string
	 * COMP: O(n)
	 */

	bool buscarHastag(string hastag);

	// operaciones con DM

	/*
	 * DESC: Envia a un destinatario concreto un mensaje privado y se almacena en el servidor
	 * PRE: La instancia debe estar creada correctamente, el usuario debe existir en la lista de usuarios y el texto <= 256 caracteres
	 * POST: Envia el mensaje privado al servidor
	 * PARAM: remite, destino, texto de tipo string
	 * COMP: O(1)
	 */

	void enviarDM(string remite, string destino, string texto);

	/*
	 * DESC: Vuelca desde el servidor a la cola DM los mensajes privados enviados al usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Muestra por pantalla los mensajes enviados al usuario y los almacena en la cola DM
	 * PARAM: id de tipo string
	 * COMP: O(n)
	 */

	void recibirDM(string id);

	/*
	 * DESC: Borra el primer mensaje pendiente de la cola DM
	 * PRE: La instancia debe estar creada correctamente y la cola no debe estar vacia
	 * POST: Elimina el primer mensaje de la cola DM
	 * PARAM: ---
	 * COMP: O(1)
	 */

	void borrarDM();

	/*
	 * DESC: Muestra por pantalla el primer mensaje pendiente
	 * PRE: la cola no debe estar vacia
	 * POST: Muestra por pantalla el primer mensaje de la cola DM
	 * PARAM: ---
	 * COMP: O(1)
	 */

	void listarPrimerDM();

	/*
	 * DESC: Responde al primer mensaje pendiente del usuario y lo elimina de la cola DM
	 * PRE: la cola DM no debe estar vacia
	 * POST: Responde al mensaje privado y lo elimina de la cola
	 * PARAM: remitente y texto de tipo string
	 * COMP: O(1)
	 */

	bool contestarDM(string remitente, string texto);

	/*
	 * DESC: Vuelca los mensajes privados almacenados en DM en un fichero
	 * PRE: cola DM no vacia
	 * POST: el fichero contiene los mensajes privados de la cola DM y la cola queda vacia de mensajes
	 * PARAM: nombre e id de tipo string
	 * COMP: O(n)
	 */

	void volcarColaDM(string nombre, string id);

	/*
	 * DESC: Recorre la cola DM obteniendo los mensajes almacenados e insertandolos en el fichero
	 * PRE: DM no vacio
	 * POST: almacena en el fichero los mensajes de DM y los elimina de la cola
	 * PARAM: flujo f de entrada/salida de tipo ofstream, id de tipio string
	 * COMP: O(n)
	 */

	void recorrerColaDM(ofstream &f, string id);

	/*
	 * DESC: Carga los mensajes privados almacenados en el fichero en la cola DM
	 * PRE: fichero no vacio
	 * POST: DM contiene los mensajes almacenados en el fichero
	 * PARAM: nombre e id de tipo string
	 * COMP: O(n)
	 */

	void cargarFicheroEnCola(string nombre, string id);

	// estadisticas
	/*
	 * DESC: Devuelve el numero de mensajes publicos almacenados
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve un entero con el numero de mensajes almacenados en la lista publicos
	 * PARAM: ---
	 * COMP: O(1)
	 */

	int numeroMensajes();

	/*
	 * DESC: Devuelve el numero de reenvios realizado por el usuario
	 * PRE: publicos no vacio
	 * POST: Devuelve un entero con el numero de reenvios realizados por el usuario que maneja la aplicacion
	 * PARAM: id de tipo string
	 * COMP: O(n)
	 */

	int numeroRT(string id);

	/*
	 * DESC: Devuelve las veces que se menciona al usuario en la lista de mensajes publicos
	 * PRE: publicos no vacio
	 * POST: Devuelve el numero de veces que se menciona al usuario en la lista de mensajes publicos
	 * PARAM: id de tipo string
	 * COMP: O(n)
	 */

	int numeroidentificador(string id);

	void volcarEnFicheroPublicos(Usuario *user1, Usuario *user2,
			string nombre_fichero);
};

#endif /* GESTORMENSAJES_H_ */
