/*
 * cola.h
 *
 *  Created on: 02/04/2014
 *      Author: juanlu
 */

#ifndef COLA_H_
#define COLA_H_
#include <iostream>
using namespace std;

template<class TipoDato>
class Cola {

private:

	class Nodo {

	public:

		TipoDato dato;

		Nodo *siguiente;

		Nodo(TipoDato dato) {
			this->dato = dato;
			this->siguiente = NULL;
		}
	};

	Nodo *frente;

	Nodo *fin;

public:
	/*
	 * DESC: Crea la instancia de la clase cola
	 * PRE: ---
	 * POST: Cola vacia
	 * PARAM: ---
	 * COMP: O(1)
	 */
	Cola();
	/*
	 * DESC: Devuelve si la cola esta vacia
	 * PRE: La instancia debe estar creada correctamente
	 * POST: Devuelve true si la cola esta vacia. False en caso contrario
	 * PARAM: ---
	 * COMP: O(1)
	 */
	bool vacia() const;
	/*
	 * DESC: Devuelve el primer elemento de la cola
	 * PRE: La cola debe estar creada correctamente
	 * POST: El dato pasado como parametro de entrada/salida contiene el valor del primer elemento de la cola
	 * PARAM: dato de tipo TipoDato de entrada/salida
	 * COMP: O(1)
	 */
	void primero(TipoDato &dato) const;
	/*
	 * DESC: Añade un elemento al final de la cola
	 * PRE: La cola debe estar creada correctamente
	 * POST: La cola contiene un elemento mas al final de la misma
	 * PARAM: dato de tipo TipoDato de entrada/salida y de caracter const
	 * COMP: O(1)
	 */
	void encolar(const TipoDato &dato);
	/*
	 * DESC: Elimina el primer elemento de la cola
	 * PRE: La cola debe estar creada correctamente
	 * POST: La cola contiene un elemento menos
	 * PARAM: ---
	 * COMP:O(1)
	 */
	void desencolar();

	/*
	 * DESC: Elimina la instancia de la clase cola
	 * PRE: La cola debe estar creada correctamente
	 * POST: Elimina la instancia cola de memoria
	 * PARAM: ---
	 * COMP:O(1)
	 */

	~Cola();
};

template<class TipoDato>
Cola<TipoDato>::Cola() {
	frente = NULL;
	fin = NULL;

}

template<class TipoDato>
bool Cola<TipoDato>::vacia() const {
	return (frente == NULL);
}

template<class TipoDato>
void Cola<TipoDato>::primero(TipoDato &dato) const {
	if (vacia())
		cout << "No hay datos" << endl;
	else
		dato = frente->dato;
}

template<class TipoDato>
void Cola<TipoDato>::encolar(const TipoDato &dato) {
	Nodo *aux = new Nodo(dato);
	if (frente == NULL)
		frente = aux;
	else
		fin->siguiente = aux;
	fin = aux;
}

template<class TipoDato>
void Cola<TipoDato>::desencolar() {

	Nodo *aux;

	aux = frente;
	frente = frente->siguiente;

	delete aux;
}

template<class TipoDato>
Cola<TipoDato>::~Cola() {

	Nodo *aux;

	while (!vacia()) {
		aux = frente;
		frente = frente->siguiente;
		delete aux;
	}

	frente = NULL;
	fin = NULL;
}

#endif /* COLA_H_ */
