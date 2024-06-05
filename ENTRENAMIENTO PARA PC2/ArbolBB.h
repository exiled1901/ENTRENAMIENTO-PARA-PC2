#ifndef __ARBOLBB_H__
#define __ARBOLBB_H__
#include "Nodo.h"
#include <functional> //LAMBDAS
using namespace std;

//template <class T>
//class Nodo {
//public:
//	T elemento; //elemento generico
//	Nodo* izq; //Nodo izquierdo del nodo padre
//	Nodo* der; //Nodo derecho del nodo padre
//};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp; //Lambda para comparar los datos

	Nodo<T>* raiz; //Puntero al nodo raíz
	void(*procesar)(T); //Puntero a funcion para procesar, se va a utilizar para procesar los datos de nuestros nodos al hacer los recorridos

	Comp comparar; // lambda de criterio de comparación
	float precioTotal;

private:
	bool _buscar(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _obtener(nodo->der, e);
			}
			else {
				return _obtener(nodo->izq, e);
			}
		}
	}
	bool _esVacia() {
		return raiz == nullptr;
	}
	//bool _insertar(Nodo<T>*& nodo, T e) {
	//	if (nodo == nullptr) {
	//		nodo = new Nodo<T>();
	//		nodo->elemento = e;
	//		return true;
	//	}
	//	else {
	//		int r = comparar(nodo->elemento, e);
	//		if (r == 0) return false;
	//		else if (r < 0) {
	//			return _insertar(nodo->der, e);
	//		}
	//		else {
	//			return _insertar(nodo->izq, e);
	//		}
	//	}
	//}
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>();
			nodo->elemento = e;
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) {
				procesar(nodo->elemento);
				procesar(e);
				return _insertar(nodo->izq, e);
			}
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}
	void _preOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	void _eliminarMemoria(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_eliminarMemoria(nodo->izq);
		_eliminarMemoria(nodo->der);
		delete nodo;
	}
	//agregar el recorrido por niveles
	int _numNivel(Nodo<T>* nodo, int nivel) {
		if (nodo != NULL && nivel == 0)
		{
			return 1;
		}
		int nivel_izq = 0; int nivel_der = 0;
		if (nodo->izq != NULL)
		{
			nivel_izq = _numNivel(nodo->izq, nivel - 1);
		}
		if (nodo->der != NULL)
		{
			nivel_der = _numNivel(nodo->der, nivel - 1);
		}
		return nivel_izq + nivel_der;
	}
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
	int _altura(Nodo<T>* nodo) {
		//La altura del árbol es:
		//	0 si es vacío
		//	la mayor de las alturas por la izquierda y por la derecha, las cuáles son 0 si son vacías ó 1 + la altura por la izq(o der) en caso contrario

		if (nodo == nullptr)
			return 0;
		else
		{
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}

	T _minimo(Nodo<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);
	}
	T _maximo(Nodo<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}
	//Agregar el predecesor y sucesor
	bool _eliminar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) {
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {
				return _eliminar(nodo->izq, e);
			}
			else { // r==0 es porque se encontró el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) {//caso 1
					nodo = nullptr;
					delete nodo;
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2
					Nodo<T>* der = nodo->der; //guardar la referencia al hijo derecho
					delete nodo; //liberar memoria del nodo
					nodo = der; //reemplazar el nodo con su hijo derecho
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3
					Nodo<T>* izq = nodo->izq;
					delete nodo;
					nodo = izq;
					return true;
				}
				else { //caso 4
					//reemplaza el nodo por su sucesor
					Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}
public:
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = [](T a, T b)->int {return a - b; };
		raiz = nullptr;
		precioTotal = 0.0;
	}
	ArbolBB(void(*otroPunteroAFuncion)(T), Comp _comparar) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = _comparar;
		raiz = nullptr;
	}
	bool esVacia() {
		return _esVacia();
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	void eliminarMemoria() {
		_eliminarMemoria(raiz);
		raiz = nullptr;
	}
	int numNivel() {
		return _numNivel(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	T Minimo() {
		return _minimo(raiz);
	}
	T Maximo() {
		return _maximo(raiz);
	}
	float getPrecioT() {
		return this->precioTotal;
	}
	void setPrecioT(float precioTotal) {
		this->precioTotal = precioTotal;
	}
	//Agregar el predecesor y sucesor
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
	float aplicarDescuento(float precioTotal, const function<float(float)>& descuentoLam) {
		return descuentoLam(precioTotal);
	}
	Nodo<T>*getRaiz() {
		return raiz;
	}
};

#endif
