/*
 * Usuario.h
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>

using namespace std;

class Usuario {

	string idUser;
	string nombre;
	string apellidos;
	string bio;
	string email;
	friend class ComparaPtrUsuarios;
public:
	/*
	 * DESC: Crea la instancia de la clase usuario
	 * PRE: ---
	 * POST: La instancia de la clase usuario queda creada
	 * PARAM: ---
	 * COMP: O(1)
	 */
	Usuario();

	/*
	 * DESC: Crea la instancia de la clase usuario
	 * PRE: ---
	 * POST: La instancia de la clase usuario queda creada con los valores pasados como parametros
	 * PARAM: id de tipo string
	 * COMP: O(1)
	 *¡*/
	Usuario(string id);

	/*
	 * DESC: Crea la instancia de la clase usuario
	 * PRE: ---
	 * POST: La instancia de la clase usuario queda creada con los valores pasados como parametros
	 * PARAM: id,nombre y apellidos de tipo string
	 * COMP: O(1)
	 *¡*/
	Usuario(string id, string nombre, string apellidos);
	/*
	 * DESC: Crea la instancia de la clase usuario
	 * PRE: ---
	 * POST: La instancia de la clase usuario queda creada con los valores pasados como parametros
	 * PARAM: id, nombre, apellidos, bio y email de tipo string
	 * COMP: O(1)
	 */
	Usuario(string id, string nombre, string apellidos, string bio,
			string email);
	/*
	 * DESC: Crea la instancia de la clase usuario
	 * PRE: ---
	 * POST: La instancia de la clase usuario queda creada con el valor del usuario pasado como parametro
	 * PARAM: puntero a user de tipo Usuario de entrada/salida
	 * COMP: O(1)
	 */
	Usuario(Usuario * &user);
	/*
	 * DESC: Da valor al id del usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: El id del usuario obtiene el valor pasado como parametro
	 * PARAM: id de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerId(const string id);
	/*
	 * DESC: Da valor al nombre del usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: El nombre del usuario obtiene el valor pasado como parametro
	 * PARAM: nombre de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerNombre(const string nombre);
	/*
	 * DESC: Da valor a los apellidos del usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Los apellidos del usuario obtienen el valor pasado como parametro
	 * PARAM: apellido de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerApellidos(const string apellidos);
	/*
	 * DESC: Da valor a la biografia del usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: La biografia del usuario obtiene el valor pasado como parametro
	 * PARAM: bio de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerBio(const string bio);
	/*
	 * DESC: Da valor al email del usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: El email del usuario obtiene el valor pasado como parametro
	 * PARAM: email de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerEmail(const string email);
	/*
	 * DESC: Devuelve el valor del id del usuario
	 * PRE: La instancia debe estar creada correctamente e id!=NULL
	 * POST: Devuelve el valor del id del usuario a traves del parametro de entrada/salida
	 * PARAM: id de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerId(string &id);
	/*
	 * DESC: Devuelve el valor del nomber del usuario
	 * PRE: La instancia debe estar creada correctamente y nombre!=NULL
	 * POST: Devuelve el valor del nombre del usuario a traves del parametro de entrada/salida
	 * PARAM: nombre de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerNombre(string &nombre);
	/*
	 * DESC: Devuelve el valor de los apellidos del usuario
	 * PRE: La instancia debe estar creada correctamente y apellido!=NULL
	 * POST: Devuelve el valor de los apellidos del usuario a traves del parametro de entrada/salida
	 * PARAM: apellidos de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerApellido(string &apellidos);
	/*
	 * DESC: Devuelve el valor de la biografia del usuario
	 * PRE: La instancia debe estar creada correctamente y bio!=NULL
	 * POST: Devuelve el valor de la biografia del usuario a traves del parametro de entrada/salida
	 * PARAM: bio de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerBio(string &bio);
	/*
	 * DESC: Devuelve el valor del email del usuario
	 * PRE: La instancia debe estar creada correctamente y email!=NULL
	 * POST: Devuelve el valor del email del usuario a traves del parametro de entrada/salida
	 * PARAM: email de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerEmail(string &email);

	/*
	 * DESC: Muestra los datos del usuario por pantalla
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Muestra por pantalla el valor de los atributos de la instancia de usuario
	 * PARAM: ---
	 * COMP: O(1)
	 */
	void mostrar();

	bool operator ==(const Usuario &user);
	void operator =(const Usuario *&user);
	bool operator !=(const Usuario &user);
	bool operator <(const Usuario &user);
	bool operator >(const Usuario &user);

	bool operator ()(const Usuario *user1, const Usuario *user2);
	bool operator ()(const Usuario &user1, const Usuario &user2);

	/*
	 * DESC: Elimina la instancia de usuario
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Elimina la instancia de usuario de memoria
	 * PARAM: ---
	 * COMP: O(1)
	 */
	~Usuario();
};

class ComparaPtrUsuarios {
public:
	int operator()(const Usuario *user1, const Usuario *user2) const {
		if (user1->idUser == user2->idUser)
			return 0;
		else if (user1->idUser< user2->idUser)
			return -1;
		else
			return 1;
	}
};

#endif /* USUARIO_H_ */
