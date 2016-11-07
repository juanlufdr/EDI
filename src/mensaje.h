/*
 * mensaje.h
 *
 *  Created on: 09/01/2014
 *      Author: Profesores de EDI
 */

#ifndef MENSAJE_H_
#define MENSAJE_H_

#include <string>

using namespace std;

class Mensaje {
	int id;
	string remitente;
	string destino;
	string texto;

public:
	/*
	 * DESC: Crea la instancia de la clase mensaje
	 * PRE: ---
	 * POST: La instancia de la clase mensaje queda creada
	 * PARAM: ---
	 * COMP: O(1)
	 */
	Mensaje();
	/*
	 * DESC: Crea la instancia de la clase mensaje
	 * PRE: ---
	 * POST: La instancia de la clase queda creada con los valores pasados como parametros
	 * PARAM: remitente, destino y texto de tipo string
	 * COMP: O(1)
	 */
	Mensaje(string remitente, string destino, string texto);

	/*
	 * DESC: Inicializa el valor del id del mensaje
	 * PRE: La instancia debe estar creada
	 * POST: El id del mensaje obtiene el valor pasado como parametro
	 * PARAM: id de tipo entero de caracter const
	 * COMP: O(1)
	 */
	void ponerId(const int id);
	/*
	 * DESC: Inicializa el valor del remitente  del mensaje
	 * PRE: La instancia debe estar creada
	 * POST: El remitente del mensaje obtiene el valor pasado como parametro
	 * PARAM: remitente de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerRemite(const string remitente);
	/*
	 * DESC: Inicializa el valor del destino del mensaje
	 * PRE: La instancia debe estar creada
	 * POST: El destino del mensaje obtiene el valor pasado como parametro
	 * PARAM: destino de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerDestino(const string destino);
	/*
	 * DESC: Inicializa el valor del texto del mensaje
	 * PRE: La instancia debe estar creada
	 * POST: El texto del mensaje obtiene el valor pasado como parametro
	 * PARAM: texto de tipo string de caracter const
	 * COMP: O(1)
	 */
	void ponerTexto(const string texto);
	/*
	 * DESC: Devuelve el valor del id del mensaje
	 * PRE: La instancia debe estar creada correctamente e id!=NULL
	 * POST: Devuelve el valor del id del mensaje a traves del parametro de entrada/salida
	 * PARAM: id de tipo entero de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerId(int &id);
	/*
	 * DESC: Devuelve el valor del remitente del mensaje
	 * PRE: La instancia debe estar creada correctamente e remitente!=NULL
	 * POST: Devuelve el valor del remitente del mensaje a traves del parametro de entrada/salida
	 * PARAM: remitente de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerRemite(string &remitente);
	/*
	 * DESC: Devuelve el valor del destino del mensaje
	 * PRE: La instancia debe estar creada correctamente e destino!=NULL
	 * POST: Devuelve el valor del destino del mensaje a traves del parametro de entrada/salida
	 * PARAM: destino de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerDestino(string &destino);
	/*
	 * DESC: Devuelve el valor del texto del mensaje
	 * PRE: La instancia debe estar creada correctamente e texto!=NULL
	 * POST: Devuelve el valor del texto del mensaje a traves del parametro de entrada/salida
	 * PARAM: texto de tipo string de entrada/salida
	 * COMP: O(1)
	 */
	void obtenerTexto(string &texto);
	/*
	 * DESC: Muestra un mensaje por pantalla
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Muestra por pantalla el valor de los atributos del mensaje
	 * PARAM: ---
	 * COMP:  O(1)
	 */
	void mostrar();
	/*
	 * DESC: Compara dos instancias de la clase mensaje
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve true si la primera instancia es menor. False en caso contrario
	 * PARAM: Puntero a msg de tipo Mensaje con caracter const
	 * COMP: O(1)
	 */
	bool operator <(const Mensaje *msg);
	/*
	 * DESC: Compara dos instancias de la clase mensaje
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve true si la primera instancia es mayor. False en caso contrario
	 * PARAM: Puntero a msg de tipo Mensaje con caracter const
	 * COMP: O(1)
	 */
	bool operator >(const Mensaje *msg);
	/*
	 * DESC: Compara dos instancias de la clase mensaje
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve true si la primera instancia es igual a la segunda. False en caso contrario
	 * PARAM: Puntero a msg de tipo Mensaje con caracter const
	 * COMP: O(1)
	 */
	bool operator ==(const Mensaje *msg);
	;
	/*
	 * DESC: Elimina la instancia de la clase mensaje
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Elimina la instancia de mensaje de memoria
	 * PARAM: ---
	 * COMP: O(1)
	 */
	~Mensaje();
};

#endif /* MENSAJE_H_ */
