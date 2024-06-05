#pragma once
#include "iostream"
#include "string"
#include "sstream"
using namespace std;

class Registro
{
private:
	int iso_code;
	string continent;
	string location;
	int total_cases;
	int total_deaths;
	int total_cases_per_million;
	int total_deaths_per_million;
public:
	Registro(int iso_code, string continent, string location, int total_cases, int total_deaths, int total_cases_per_million, int total_deaths_per_million);
	~Registro();
	string toString() {
		stringstream s;
		s << "Iso Code:\t" << this->iso_code << endl
			<< "Continent:\t" << this->continent << endl
			<< "Location:\t" << this->location << endl
			<< "Total cases:\t" << this->total_cases << endl
			<< "Total deaths:\t" << this->total_deaths << endl
			<< "Total cases per million:\t" << this->total_cases_per_million << endl
			<< "Total deaths per million:\t" << this->total_deaths_per_million << endl;
		return s.str();
	}
	int getIso_Code() {
		return this->iso_code;
	}
	string getContinent() {
		return this->continent;
	}
	string getLocation() {
		return this->location;
	}
	int getTotal_Cases() {
		return this->total_cases;
	}
	int getTotal_Deaths() {
		return this->total_deaths;
	}
	int getT_cases_PM(){
		return this->total_cases_per_million;
	}
	int getT_deaths_PM() {
		return this->total_deaths_per_million;
	}
};
Registro::Registro(int iso_code, string continent, string location, int total_cases, int total_deaths, int total_cases_per_million, int total_deaths_per_million)
{
	this->iso_code = iso_code;
	this->continent = continent;
	this->location = location;
	this->total_cases = total_cases;
	this->total_deaths = total_deaths;
	this->total_cases_per_million = total_cases_per_million;
	this->total_deaths_per_million = total_deaths_per_million;
}

Registro::~Registro()
{
}