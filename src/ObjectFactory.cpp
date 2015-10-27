/*
 * ObjectFactory.cpp
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#include "ObjectFactory.h"
#include "GameObject.h"
#include "Objetos/Arbolit.h"
#include "Objetos/Castillo.h"
#include "Objetos/Suelo.h"
#include "Objetos/Molino.h"

namespace std {

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
	return objetoACargar;


}

}
