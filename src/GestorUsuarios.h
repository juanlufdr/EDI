/*
 * GestorUsuarios.h

 *
 *  Created on: 24/03/2014
 *  Author: Juan Luis Fragoso del Rey
 *  Descripcion : Gestiona todo lo relaciona con los usuarios y seguidos
 */
#include <iostream>
#include "usuario.h"
#include "svr_interfaz.h"
#include "listapi.h"
#include "arbol.h"
#include "cola.h"
#include <fstream>
using namespace std;

#ifndef GESTORUSUARIOS_H_
#define GESTORUSUARIOS_H_

class GestorUsuarios {
private:
	SVR_interfaz *svrifaz; // objeto del servidor que nos permite obtener datos del mismo
	Usuario *usuario; // objeto de la clase usuario utilizado para identificar al usuario que trabaja con la aplicacion
	ListaPI<Usuario*> *rsuexUsuarios; // Puntero a ListaPI de punteros a usuarios que almacena todos los usuarios registrados en el servidor
	Arbol<Usuario*, ComparaPtrUsuarios> *seguidos;

	/*
	 * DESC: Pinta un menu para la opcion de modificar el perfil
	 * PRE: instancia creada correctamente
	 * POST: En pantalla aparece un menu con las opciones de modificacion de perfil
	 * PARAM: ---
	 * COMP: O(1)
	 */

	void pintarMenuModificacion();

	/*
	 * DESC: metodo privado que inserta usuarios por orden alfabetico en la lista rsuexUsuarios
	 * PRE: La lista rsuexUsuarios debe estar creada
	 * POST: la lista rsuexusuarios queda ordenada alfabeticamente
	 * PARAM: Puntero a *user de tipo Usuario*
	 * COMP: O(n)
	 */

	void insertarOrdenEnLista(Usuario* user);

	/*
	 * DESC:  Funcion recursiva que muestra los valores del arbol abbu, un arbol binario de busqueda.
	 * PRE:   abbu != NULL
	 * POST: ---
	 * PARAM:  puntero a abbu de tipo Arbol<Usuario*, ComparaPtrUsuario>
	 * COMP:  O(n)
	 */

	void inOrden(Arbol<Usuario *, ComparaPtrUsuarios> *abbu);

	/*
	 * DESC: Funcion recursiva que filtra un arbol abbu, un arbol binario de busqueda, y muestra los nodos cuyo Id empieza por el valor del parametro id.
	 * PRE: abbu != NULL
	 * POST: ---
	 * PARAM: puntero a abbu de tipo Arbol<Usuario*, ComparaPtrUsuario>, const id de entrada/salida de tipo string
	 * COMP:  O(n)
	 */

	bool filtroInOrden(Arbol<Usuario *, ComparaPtrUsuarios> *abbu,
			const string &id);

	/*
	 * DEeSC: Funcion que averigua si una cadena empieza por otra cadena.
	 * PRE: cad != vacia
	 * POST: true si cad empieza por subcad, false en caso contrario
	 * PARAM: cad de tipo string, subcad de tipo string
	 * COMP:  O(1)
	 */

	bool empiezaPor(string cad, string subcad);

	/*
	 * DESC: Funcion recursiva que busca y devuelve un subarbol del arbol abbu, (un arbol binario de busqueda), con los usuarios hijos del primer nodo que empieza por el parametro id
	 * PRE: abbu != NULL
	 * POST: Puntero al subarbol que contiene como raiz el primero usuario encontrado que empieza por id.
	 * PARAM: abbu de tipo Arbol<Usuario*, ComparaPtrUsuario>, const id de entrada/salida de tipo string
	 * COMP:  O(log n) si balanceado
	 */

	Arbol<Usuario *, ComparaPtrUsuarios> * similares(
			Arbol<Usuario *, ComparaPtrUsuarios> *abbu, const string &id);

	/*
	 * DESC: Almacena en el fichero los usuarios almacenados en el arbol
	 * PRE: arbol no vacio
	 * POST: el fichero contiene los usuarios almacenados en seguidos
	 * PARAM: puntero abbu de tipo Arbol<Usuario *, ComparaPtrUsuarios>, nombre de tipo string
	 * COMP: O(n)
	 */

	void volcarArbolSeguidos(Arbol<Usuario *, ComparaPtrUsuarios> *abbu,
			string nombre);

	/*
	 * DESC: se realiza un recorrido del arbol seguidos en preorden
	 * PRE: arbol no vacio
	 * POST: recorre el arbol en preorden
	 * PARAM: puntero a abbu de tipo Arbol<Usuario*, ComparaPtrUsuario>, flujo f de entrada/salida de tipo ofstream
	 * COMP: O(n)
	 */

	void recorrerArbolSeguidos(Arbol<Usuario *, ComparaPtrUsuarios> *abbu,
			ofstream &f);

	/*
	 * DESC: inserta en el fichero el usuario
	 * PRE: fichero abierto correctamente
	 * POST: el fichero almacena el usuario pasado como parametro
	 * PARAM: puntero user de tipo Usuario, flujo f de entrada/salida de tipo ofstream
	 * COMP: O(1)
	 */

	void insertarSeguidosFichero(Usuario *user, ofstream &f);

	/*
	 * DESC: inserta en el fichero el usuario que maneja la aplicacion
	 * PRE: usuario creado correctamente
	 * POST: el fichero almacena los datos del usuario
	 * PARAM: id, nombre, apellidos, bio y email de tipo string
	 * COMP: O(1)
	 */

	void insertarPerfilEnFichero(string id, string nombre, string apellidos,
			string bio, string email);

public:

	/*
	 * DESC: Crea la instancia de la clase GestorUsuarios
	 * PRE: ---
	 * POST: La instancia queda creada correctamente
	 * PARAM: ---
	 * COMP: O(1)
	 */

	GestorUsuarios();

	/*
	 * DESC: Elimina la instancia de GestorUsuarios
	 * PRE: La instancia debe estar creada correctamente
	 * POST: La instancia queda eliminada de memoria
	 * PARAM: ---
	 * COMP: O(n)
	 */

	~GestorUsuarios();

	// Operaciones con usuarios

	/*
	 * DESC: elimina los usuario almacenados en la lista
	 * PRE: lista no vacioa
	 * POST: la lista queda sin usuarios almacenados
	 * PARAM: puntero a lista de entrada/salida de tipo ListaPI<Usuario*>
	 * COMP: O(n)
	 */

	void borrarListaUsuarios(ListaPI<Usuario*> *&lista);

	/*
	 * DESC: Da de alta un perfil en el servidor
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve True si el usuario a sido dado de alta correctamente, False en caso contrario
	 * PARAM: Puntero a user de tipo Usuario
	 * COMP:O(1)
	 */

	bool crearPerfil(Usuario *user);

	/*
	 * DESC:metodo que busca un usuario a través del string pasado como parametro en la lista rsuexUsuarios
	 * PRE: La lista rsuexUsuarios debe estar creada correctamente
	 * POST: Devueve true si el usuario existe, false en caso contrario
	 * PARAM: id de tipo string, puntero user de entrada/salida de tipo Usuario
	 * COMP:O(n)
	 */

	bool buscarUsuario(string id, Usuario *&user);

	/*
	 * DESC: Identifica a un usuario ya creado en el sistema
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Otorga al atributo usuario el valor del usuario identficado con el id pasado por parametro
	 * PARAM: id de tipo string
	 * COMP:O(n)
	 */

	bool identificarPerfil(string id);

	/*
	 * DESC: Modifica el perfil que tiene el id pasado como parametro
	 * PRE: La instancia debe estar creada correctamente y el usuario debe existir en la lista rsuexUsuarios
	 * POST: Modifica los atributos seleccionados por el usuario del perfil seleccionado
	 * PARAM: id de tipo string
	 * COMP:O(1)
	 */

	void modificarPerfil(string id);

	/*
	 * DESC: Elimina el perfil que se identifica con el id pasado como parametro
	 * PRE: El usuario debe existir en la lista rsuexUsuarios y la instancia debe estar creada correctamente
	 * POST: Devuelve True si el usuario ha sido eliminado de la lista, False en caso contrario. Tambien elimina su fichero
	 * PARAM: id de tipo string
	 * COMP: O(n)
	 */

	bool eliminarPerfil(string id);

	/*
	 * DESC: Almacena en la lista rsuexUsuarios todos los usuarios que contiene el servidor
	 * PRE: La lista y la instancia deben estar creadas correctamentes
	 * POST: La lista contiene todos los usuarios del servidor ordenados alfabeticamente
	 * PARAM: ---
	 * COMP: O(n²)
	 */

	void ListarUsuario();

	/*
	 * DESC: Muestra por pantalla todos los usuarios contenidos en la lista rsuexUsuarios
	 * PRE: La instancia debe estar creada correctamente y la lista no debe estar vacia
	 * POST: Muestra por pantalla los usuarios almacenados en la lista rsuexUsuarios
	 * PARAM: ---
	 * COMP: O(n)
	 */

	void mostrarListas();

	/*
	 * DESC: Devuelve el valor del id que tiene el atributo usuario
	 * PRE: La instancia debe estar creada correctamente y usuario!=NULL
	 * POST: id tienen el valor del id del atributo usuario
	 * PARAM: id de tipo string de entrada/salida
	 * COMP:O(1)
	 */

	void obtenerIdUsuario(string &id);

	// Operaciones con Seguidores

	/*
	 * DESC: Sigue al usuario que se identifica con el id pasado como parametro
	 * PRE: La instancia y las listas rsuexUsuarios y seguidores deben estar creadas correctamente
	 * POST: Almacena en la arbol seguidos el usuario cuyo id a sido pasado como parametro
	 * PARAM: puntero a id de tipo string
	 * COMP: O(log(n))
	 */

	bool seguirUsuario(string id);

	/*
	 * DESC: Muestra por pantalla todos los usuarios contenidos en el arbol seguidos
	 * PRE: La instancia debe estar creada correctamente y arbol seguidos no vacio
	 * POST: Muestra por pantalla todos los usuarios almacenados en el arbol seguidos
	 * PARAM: ---
	 * COMP: O(n)
	 */

	void mostrarSeguidos();

	/*
	 * DESC: Deja de seguir al usuario que se identifica con el id pasado como parametro
	 * PRE: La instancia debe estar creada correctamente y el usuario debe existir en el arbol seguidos
	 * POST: Elimina del arbol seguidos el usuario que se identifica con el id pasado como parametro
	 * PARAM: id de tipo string
	 * COMP: O(log(n))
	 */

	void dejarSeguir(string id);

	/*
	 * DESC: Busca el usuario usuario seguido en el arbol pasado como parametro
	 * PRE: La instancia debe estar creada correctamente y el arbol pasado como parametro no vacio
	 * POST: Devuelve el Usuario almacenado. NULL si no lo esta
	 * PARAM: id de tipo string, puntero abbu de tipo Arbol<Usuario *, ComparaPtrUsuarios>
	 * COMP: O(n)
	 */

	Usuario * buscarSeguidos(Arbol<Usuario *, ComparaPtrUsuarios> *abbu,
			const string &id);

	/*
	 * DESC: Muestra los usuarios que empiezan por el id pasado como parametro
	 * PRE: arbol seguidos no vacio
	 * POST: muestra por pantalla los usuarios que empiezan por id pasado como parametro
	 * PARAM: const id de entrada/salida de tipo string
	 * COMP: O(log n)
	 */

	void mostrarSimilares(const string &id);

	/*
	 * DESC: Devuelve el arbol de seguidos
	 * PRE: instancia creada correctamente
	 * POST: devuelve un puntero que contiene la direccion al arbol de seguidos
	 * PARAM: ---
	 * COMP: O(1)
	 */

	Arbol<Usuario*, ComparaPtrUsuarios> *obtenerSeguidos();

	/*
	 * DESC: Almacena en un fichero los usuarios seguidos
	 * PRE: Arbol seguidos no vacio
	 * POST: el fichero contiene los usuarios almacenados en arbol seguidos
	 * PARAM: flujo f de entrada/salida de tipo ofstream, puntero abb de tipo Arbol<Usuario*, ComparaPtrUsuarios>
	 * COMP: O(n²)
	 */

	void volcarFicheroEnArbol(ifstream &f,
			Arbol<Usuario*, ComparaPtrUsuarios> *abb);

	// estadisticas

	/*
	 * DESC: Devuelve el numero de usuarios seguidos
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve un entero con el numero de seguidos
	 * PARAM: puntero abbu de tipo Arbol<Usuario *, ComparaPtrUsuarios>
	 * COMP: O(n)
	 */

	int contarSeguidos(Arbol<Usuario *, ComparaPtrUsuarios> *abbu);

	/*
	 * DESC: Proporciona el numero de usuarios registrados
	 * PRE: La instancia debe estar creada correctamente y la lista rsuexUsuarios no debe estar vacia
	 * POST: Devuelve un entero con el numero de usuarios en la lista rsuexUsuarios
	 * PARAM: ---
	 * COMP: O(n)
	 */

	int numeroUsuarios();

	Arbol<Usuario *, ComparaPtrUsuarios> * obtenerArbolporId(Arbol<Usuario *, ComparaPtrUsuarios> *&abb,string id);

	void obtenerUsuariosArbol(Arbol<Usuario *, ComparaPtrUsuarios> *abb, Usuario *&user1, Usuario *&user2);

};

#endif /* GESTORUSUARIOS_H_ */
