#ifndef __NODO_H__
#define __NODO_H__

template<class T>
class Nodo {
public:
	T dato;
	T elemento;
	Nodo<T>* siguiente;
	Nodo<T>* izq;
	Nodo<T>* der;
	Nodo() : izq(nullptr), der(nullptr) {}
	Nodo(T v, Nodo<T>* sig = NULL) {
		dato = v;
		siguiente = sig;
	}

};

#endif