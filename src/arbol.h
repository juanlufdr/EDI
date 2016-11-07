/*
 * arbol.h

 *
 *  Created on: 28/05/2014
 *  Author: Juan Luis Fragoso del Rey
 *  Descripcion : ED utilizada para la gestion de los usuarios seguidos
 */

#ifndef _ARBOL_H
#define _ARBOL_H

#include <iostream>

using namespace std;

template<class TipoDato, class Compare>
class Arbol {

private:

	TipoDato datoRaiz;
	Arbol<TipoDato, Compare> *hIzq;
	Arbol<TipoDato, Compare> *hDer;

	bool esVacio;

	Arbol<TipoDato, Compare> *borrarOrden(TipoDato dato);

public:

	Arbol();
	Arbol(Arbol<TipoDato, Compare> *hIzq, TipoDato datoRaiz,
			Arbol<TipoDato, Compare> *hDer);

	Arbol *hijoIzq();
	Arbol *hijoDer();
	TipoDato raiz();

	bool vacio();
	bool insertar(const TipoDato &dato);
	void borrar(TipoDato dato);
	bool pertenece(const TipoDato &dato);

	~Arbol();
};

/**
 * DESC: Constructor por defecto. Construye un objeto de tipo Arbol vacio
 * PRE:---
 * POST:Instancia creada correctamente
 * PARAM: ---
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
Arbol<TipoDato, Compare>::Arbol() {

	esVacio = true;
	hIzq = NULL;
	hDer = NULL;
}

/**
 * DESC: Constructor parametrizado. Crea un objeto de tipo Arbol a partir de dos arboles (izq. y der.) y un dato.
 * PRE: ---
 * POST: Instancia creada correctamente
 * PARAM: hIzq: Arbol Hijo izquierdo del arbol a crear
 *		  dato: dato a insertar en la raiz
 * 		  hDer: Arbol Hijo derecho del arbol a crear
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
Arbol<TipoDato, Compare>::Arbol(Arbol<TipoDato, Compare> *hIzq, TipoDato dato,
		Arbol<TipoDato, Compare> *hDer) {

	esVacio = false;
	this->datoRaiz = dato;
	this->hIzq = hIzq;
	this->hDer = hDer;
}

/**
 * DESC: Devuelve el subarbol izquierdo del arbol actual.
 * PRE: Arbol no vacio
 * POST: Devuelve el subarbol izquierdo
 * PARAM: ---
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
Arbol<TipoDato, Compare> *Arbol<TipoDato, Compare>::hijoIzq() {

	return hIzq;
}

/**
 * DESC: Devuelve el subarbol derecho del arbol actual
 * PRE: Arbol no vaciop
 * POST: Devuelve el subarbol derecho
 * PARAM: ---
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
Arbol<TipoDato, Compare> *Arbol<TipoDato, Compare>::hijoDer() {

	return hDer;
}

/**
 * DESC: Devuelve la raiz de un arbol
 * PRE: Arbol no vacio
 * POST: Devuelve la raiz del arbol
 * PARAM: ---
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
TipoDato Arbol<TipoDato, Compare>::raiz() {

	return datoRaiz;
}

/**
 * DESC: Devuelve si un arbol es vacio
 * PRE: Instancia creada correctamente
 * POST: Devuelve true si el arbol esta vacio. False en caso contrario
 * PARAM: ---
 * COMP: O(1)
 */
template<class TipoDato, class Compare>
bool Arbol<TipoDato, Compare>::vacio() {

	return esVacio;
}

/**
 * DESC: Inserta el valor dato en el Arbol Binario de Busqueda
 * PRE: el dato pasado como parametro no pertenece al arbol
 * POST: si el dato se encuentra en el arbol, el arbol no se modifica
 * PARAM: dato: Valor a insertar
 * COMP: O(log(n))
 */
template<class TipoDato, class Compare>
bool Arbol<TipoDato, Compare>::insertar(const TipoDato &dato) {

	bool resultado = true;
	Compare c;

	if (vacio()) {
		datoRaiz = dato;
		esVacio = false;
	} else {

		if (c.operator()(dato, datoRaiz) != 0) {

			Arbol<TipoDato, Compare> *aux;

			if (c.operator()(dato, datoRaiz) < 0) {
				aux = hijoIzq();
				if (aux == NULL) {
					hIzq = aux = new Arbol<TipoDato, Compare>();
				}
			} else {
				aux = hijoDer();
				if (aux == NULL) {
					hDer = aux = new Arbol<TipoDato, Compare>();
				}
			}
			resultado = aux->insertar(dato);

		} else {
			resultado = false;
		}
	}
	return resultado;
}

/**
 * DESC: Elimina el nodo que contenga el valor de dato
 * PRE: arbol no vacio
 * POST: ---
 * PARAM: dato: Valor a eliminar
 * COMP: O(log(n))
 */
template<class TipoDato, class Compare>
void Arbol<TipoDato, Compare>::borrar(TipoDato dato) {

	Compare c;

	if (!vacio()) {

		if (c.operator()(dato, datoRaiz) < 0) {

			if (hIzq != NULL)
				hIzq = hIzq->borrarOrden(dato);

		} else if (c.operator()(dato, datoRaiz) > 0) {

			if (hDer != NULL)
				hDer = hDer->borrarOrden(dato);

			// Encontrado el dato a borrar: datoRaiz
		} else {

			if ((hIzq == NULL) && (hDer == NULL)) {
				esVacio = true;
			} else {
				borrarOrden(dato);
			}

		}

	}
}

/**
 * DESC: Metodo privado auxiliar para realizar el borrado de un nodo. Reestructura el arbol tras el borrado.
 * PRE: arbol no vacio
 * POST: Devuelve un arbol sin el dato pasado como parametro
 * PARAM: dato: Valor a eliminar
 * COMP: O(log(n))
 */

template<class TipoDato, class Compare>
Arbol<TipoDato, Compare> *Arbol<TipoDato, Compare>::borrarOrden(TipoDato dato) {

	TipoDato datoaux;
	Arbol *retorno = this, *aborrar, *candidato, *antecesor;
	Compare c;

	if (!vacio()) {

		if (c.operator()(dato, datoRaiz) < 0) {

			if (hIzq != NULL)
				hIzq = hIzq->borrarOrden(dato);

		} else if (c.operator()(dato, datoRaiz) > 0) {
			if (hDer != NULL)
				hDer = hDer->borrarOrden(dato);

		} else {

			aborrar = this;

			// 1. Si es hoja:
			if ((hDer == NULL) && (hIzq == NULL)) {

				delete aborrar;
				retorno = NULL;

			} else {

				// 2. Solo tiene un hijo
				// 2.1. Solo hijo izquierdo:
				if (hDer == NULL) {

					aborrar = hIzq;
					datoaux = datoRaiz;
					datoRaiz = hIzq->raiz();
					hIzq->datoRaiz = datoaux;
					hIzq = hIzq->hijoIzq();
					hDer = aborrar->hijoDer();

					retorno = this;

					// 2.2. Solo hijo derecho:
				} else if (hIzq == NULL) {

					aborrar = hDer;
					datoaux = datoRaiz;
					datoRaiz = hDer->raiz();
					hDer->datoRaiz = datoaux;
					hDer = hDer->hijoDer();
					hIzq = aborrar->hijoIzq();

					retorno = this;

					// 3. Tiene dos hijos.
				} else {

					candidato = hijoIzq();
					antecesor = this;
					while (candidato->hijoDer()) {
						antecesor = candidato;
						candidato = candidato->hijoDer();
					}

					// Intercambio de datos de candidato
					datoaux = datoRaiz;
					datoRaiz = candidato->raiz();
					candidato->datoRaiz = datoaux;
					aborrar = candidato;
					if (antecesor == this) {
						hIzq = candidato->hijoIzq();
					} else {
						antecesor->hDer = candidato->hijoIzq();
					}
				}

				//Eliminar solo ese nodo, no todo el subarbol
				aborrar->hIzq = NULL;
				aborrar->hDer = NULL;
				delete aborrar;
			}
		}

	}

	return retorno;
}

/**
 * DESC: Busqueda de un dato en el arbol.
 * PRE: arbol no vacio
 * POST: devuelve true si el dato se encuetra en el arbol. False en caso contrario
 * PARAM: dato: valor a buscar en el arbol
 * COMP: O(log(n))
 */
template<class TipoDato, class Compare>
bool Arbol<TipoDato, Compare>::pertenece(const TipoDato &dato) {

	bool enc = false;
	Compare c;

	if (vacio()) {

		enc = false;

	} else {

		Arbol<TipoDato, Compare> *aux;

		if (c.operator()(dato, datoRaiz) < 0) {

			aux = hijoIzq();
			if (aux != NULL)
				enc = aux->pertenece(dato);

			//} else if (*dato > *datoRaiz) {
		} else if (c.operator()(dato, datoRaiz) > 0) {

			aux = hijoDer();
			if (aux != NULL)
				enc = aux->pertenece(dato);

		} else {
			enc = true;
		}

	}

	return enc;
}

/**
 * DESC: Destruye un objeto de tipo Arbol, y los nodos del mismo.
 * PRE: la instancia debe estar creada correctamente
 * POST: la instancia queda borrada de memoria
 * PARAM: ---
 * COMP: O(n)
 */
template<class TipoDato, class Compare>
Arbol<TipoDato, Compare>::~Arbol() {

	Arbol<TipoDato, Compare> *aux;

	if (!vacio()) {

		aux = hijoIzq();
		if (aux != NULL)
			delete aux;

		aux = hijoDer();
		if (aux != NULL)
			delete aux;

		esVacio = true;
	}
}

#endif /* _ARBOL_H_ */

