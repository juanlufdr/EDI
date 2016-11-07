/*
 * SVR_interfaz.h
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#ifndef SVR_INTERFAZ_H_
#define SVR_INTERFAZ_H_

#include <string>

#include "listapi.h"
#include "svr_stub.h"

using namespace std;


class SVR_interfaz {

	static SVR_stub    *svr_stub;

public:

	SVR_interfaz();

	/* DESC:   Devuelve el estado de la conexion con el servidor
	 * PRE:    -
	 * POST:   -
	 * PARAM:  -
	 * RET:    true si existe conexion con el servidor, false en otro caso
	 * COMP:   O(1)
	 */
	bool  conectado         ();

    /* DESC:   Crear un usuario en la red social en el servidor.
     * PRE:    Los campos deben estar rellenos con valores adecuados.
     * POST:   El usuario se crea en el servidor (num_usuarios++)
     * PARAM:  Campos que describen al usuario (identificador, nombre, apellidos, bio y email)
     * RET:    true: si el usuario se ha insertado en RSUEx, false en otro caso (usuario existe).
     * COMP:   O(1)
     */
	bool  insertar_usuario  (string id, string nombre, string apellidos, string bio, string email);

    /* DESC:   Eliminar un usuario en la red social en el servidor.
     * PRE:    El identificador debe ser un valor valido
     * POST:   El usuario se eliminara del servidor (num_usuarios--)
     * PARAM:  Identificador de usuario
     * RET:    -
     * COMP:   O(1)
     */
	void  eliminar_usuario  (string id);

    /* DESC:   Devuelve una ListaPI con los usuarios del servidor (todos).
     *         La lista no esta ordenada
     * PRE:    ListaPI debe estar creada antes de la llamada
     * POST:   -
     * PARAM:  ListaPI de usuarios (tipo Usuario*) creada.
     * RET:    -
     * COMP:   O(n), n=numero de usuarios
     */
	void  obtener_usuarios  (ListaPI<Usuario *> * &luser);

    /* DESC:   Enviar un mensaje a la red social. Se enviar‡ al servidor.
     * PRE:    -
     * POST:   Nuevo mensaje en la red social (num_mensajes++).
     *         El servidor le asigna un nœmero de identificacion unico y creciente
     *         (aunque puede que no correlativo).
     * PARAM:  Campos que contiene un mensaje: remitente, y texto.
     *         Identificador y fecha es asignado por el servidor.
     * RET:    -
     * COMP:   O(1)
     */
	void  enviar_mensaje    (string remite, string texto);

    /* DESC:   Devuelve una ListaPI con los mensajes del servidor con identificador > id
     *         La lista esta ordenada: primero el mensaje mas reciente (por identificador)
     * PRE:    ListaPI de mensajes (tipo Mensaje*) debe estar creada antes de la llamada
     * POST:   ListaPI contiene los mensajes del servidor con identificador > id
     * PARAM:  IN id: Identificador numerico (int).
     *         OUT ListaPI: Lista de mensajes (tipo Mensaje*).
     * RET:    -
     * COMP:   O(n), n=numero de mensajes
     */
	void  obtener_mensajes  (int id, ListaPI<Mensaje *> * &lmsg);

    /* DESC:   Enviar un mensaje directo o privado a un usuario. Se enviar‡ al servidor.
     * PRE:    -
     * POST:   Nuevo mensaje en directo a un usuario (num_mensajes_directos++).
     *         El servidor le asigna un nœmero de identificacion unico y creciente
     *         (aunque puede que no correlativo)
     * PARAM:  Campos que contiene un mensaje directo: remitente, destino y texto.
     *         Identificador y fecha es asignado por el servidor.
     * RET:    -
     * COMP:   O(1)
     */
	void  enviar_dm         (string remite, string destino, string texto);

	/* DESC:   Devuelve una ListaPI con los mensajes directos al usuario con identificador id
	 *         La lista esta ordenada: primero el mas reciente (por dientificador)
     * PRE:    ListaPI de mensajes (tipo Mensaje*) debe estar creada antes de la llamada
     * POST:   ListaPI contiene los mensajes del servidor con identificador de usuario = id
     * PARAM:  IN id: Identificador de usuario.
     *         OUT ListaPI: Lista de mensajes (tipo Mensaje*).
     * RET:    -
     * COMP:   O(n), n=numero de mensajes
     */
	void  recibir_dms       (string id, ListaPI<Mensaje *> *&ldm);

	~SVR_interfaz();
};

#endif /* SVR_INTERFAZ_H_ */
