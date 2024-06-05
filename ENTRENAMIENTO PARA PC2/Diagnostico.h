#pragma once
#include "Registro.h"
#include "ArbolBB.h"
#include "p_queue.h"
#include "iostream"
#include <functional>
#include <vector>
class Diagnostico
{
private:
	//Registro* registro;
	ArbolBB<Registro*>* arbolBB;
	p_queue* colaDePrioridad;
	//priority_queue<Registro*, vector<Registro*>, function<bool(Registro*, Registro*)>> colaDePrioridad;
public:
	Diagnostico();
	~Diagnostico();
	//void imprimirArbol(Registro* registro);
	void indexar_ArbolBB(Registro* reg);
	void mostrarEnOrden();
	void mostrarEstadisticas();
	void insertarEnColadePrioridad();
	void mostrarTop5MenorFallecidos();
	//list<Registro> obtenerMenores
};

Diagnostico::Diagnostico()
{
	auto imprimirArbol = [](Registro* r) {
		cout << r->toString() << endl;
		};
	arbolBB = new ArbolBB<Registro*>(imprimirArbol, [](Registro* registro1, Registro* registro2) {
		return registro1->getT_cases_PM() - registro2->getT_cases_PM();
		});
	//colaDePrioridad = priority_queue<Registro*, vector<Registro*>, function<bool(Registro*, Registro*)>>(
	//	[](Registro* registro1, Registro* registro2) {
	//		return registro1->getTotal_Deaths() > registro2->getTotal_Deaths();
	//	}
	//);
	colaDePrioridad = new p_queue(nullptr, 0);
}

Diagnostico::~Diagnostico()
{
	delete arbolBB;
	delete colaDePrioridad;
}
void Diagnostico::indexar_ArbolBB(Registro* reg){
	if (reg != nullptr) {
		arbolBB->insertar(reg);
	}
}
void Diagnostico::mostrarEnOrden() {
	arbolBB->enOrden();
}
void Diagnostico::mostrarEstadisticas() {
	int totalRegistros = arbolBB->cantidad();

	cout << "Cantidad de registros en el arbol: " << totalRegistros << endl;

	Registro* minRegistro = arbolBB->Minimo();
	Registro* maxRegistro = arbolBB->Maximo();

	if (minRegistro != nullptr) {
		cout << "\nDATOS DEL PAIS CON MENOS CASOS POR MILLON: " << "\n" << minRegistro->toString() << endl;
	}

	if (maxRegistro != nullptr) {
		cout << "\nDATOS DEL PAIS CON MAS CASOS POR MILLON: " << "\n" << maxRegistro->toString() << endl;
	}
}

void Diagnostico::insertarEnColadePrioridad() {
	function<void(Nodo<Registro*>*)> traverseAndInsert = [&](Nodo<Registro*>* nodo) {
		if (nodo == nullptr) return;
		traverseAndInsert(nodo->izq);
		colaDePrioridad->insert(nodo->elemento);
		traverseAndInsert(nodo->der);
		};

	traverseAndInsert(arbolBB->getRaiz());
}
void Diagnostico::mostrarTop5MenorFallecidos() {
	vector<Registro*> top5;
	for (int i = 0; i < 5 && colaDePrioridad->size() > 0; ++i) {
		top5.push_back(colaDePrioridad->extract_max());
	}

	cout << "Top 5 paises con la menor cantidad de fallecidos:" << endl;
	for (Registro* reg : top5) {
		cout << reg->toString() << endl;
	}
}
