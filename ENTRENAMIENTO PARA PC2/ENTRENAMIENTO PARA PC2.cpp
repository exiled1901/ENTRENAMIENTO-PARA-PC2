#include "pch.h"
#include "Diagnostico.h"
#include "Registro.h"
#include "string"
using namespace std;
using namespace System;

int main()
{
	Diagnostico* ctrl = new Diagnostico();
	int iso_code = 2020;
	string continent = "LATAM";
	string location = "Peru";
	int total_cases = 1200000;
	int total_deaths = 450000;
	int total_cases_per_million = total_cases / 1000000;
	int total_deaths_per_million = total_deaths / 1000000;
	Registro* registroPrueba = new Registro(iso_code, continent, location, total_cases, total_deaths, total_cases_per_million, total_deaths_per_million);
	int iso_code1 = 2020;
	string continent1 = "Europa";
	string location1 = "Alemania";
	int total_cases1 = 1250000;
	int total_deaths1 = 460000;
	int total_cases_per_million1 = total_cases / 1000;
	int total_deaths_per_million1 = total_deaths / 1000000;
	Registro* registroPrueba1 = new Registro(iso_code1, continent1, location1, total_cases1, total_deaths1, total_cases_per_million1, total_deaths_per_million1);
	
	ctrl->indexar_ArbolBB(registroPrueba);
	ctrl->indexar_ArbolBB(registroPrueba1);
	cout << "ARBOL EN ORDEN:" << endl;
	ctrl->mostrarEnOrden();

	cout << "\n\nESTADISTICAS:" << endl;
	ctrl->mostrarEstadisticas(); 

	cout << "\n\nTOP 5 MENOR FALLECIDOS:" << endl;
	ctrl->insertarEnColadePrioridad();
	ctrl->mostrarTop5MenorFallecidos();
    return 0;
}
