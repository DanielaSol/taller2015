/*
 * ObjectFactory.cpp
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#include "ObjectFactory.h"
#include "GameObject.h"
#include "Objetos/Arbolit.h"
#include "Objetos/Construcciones/Castillo.h"
#include "Objetos/Suelo.h"
#include "Objetos/Construcciones/Molino.h"
#include "Objetos/Recursos/Madera.h"
#include "Objetos/Recursos/Oro.h"
#include "Objetos/Recursos/Comida.h"

using namespace std;

ObjectFactory* ObjectFactory::objectInstance = 0;

ObjectFactory::ObjectFactory() {
	// TODO Auto-generated constructor stub

}

ObjectFactory::~ObjectFactory() {
	delete (objectInstance);
}

GameObject* ObjectFactory::crear(string tipo, int x, int y) {
	GameObject* objetoACargar = NULL;

	if(tipo == "arbol") {
		objetoACargar = new Arbolit(x,y);
	}
	else if(tipo == "castillo"){
		objetoACargar = new Castillo(x,y);
	}
	else if(tipo == "agua"){
		objetoACargar = new Suelo(x,y,"agua");
	}
	else if(tipo == "tierra"){
		objetoACargar = new Suelo(x,y,"tierra");
	}
	else if(tipo == "molino"){
		objetoACargar = new Molino(x,y);
	}
	else if(tipo == "madera") {
		objetoACargar = new Madera(x,y);
	}
	else if(tipo == "oro") {
		objetoACargar = new Oro(x,y);
	}
	else if(tipo == "comida") {
		objetoACargar = new Comida(x,y);
	}
	return objetoACargar;

}



