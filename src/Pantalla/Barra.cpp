/*
 * Barra.cpp
 *
 *  Created on: 24/10/2015
 *      Author: daniela
 */

#include "Barra.h"
#include <string>
#include <map>

using namespace std;

map<string, int> recursos;

Barra::Barra() {
	recursos.insert(pair <string,int>("Madera",0));
	recursos.insert(pair <string,int>("Oro",0));
	recursos.insert(pair <string,int>("Comida",0));

}

Barra::~Barra() {
	// TODO Auto-generated destructor stub
}

void Barra::addRecurso(string nombre, int valor) {
	std::map<string, int>::iterator it = recursos.find(nombre);
	if (it != recursos.end())
	    it->second += valor;
}

map<string, int> Barra::getMapRecursos() {
	return recursos;

}

void Barra::clean() {
	recursos.clear();
}




