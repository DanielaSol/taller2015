/*
 * Recurso.cpp
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#include "Recurso.h"

namespace std {

Recurso::Recurso() {
	// TODO Auto-generated constructor stub

}

Recurso::~Recurso() {
	// TODO Auto-generated destructor stub
}

int Recurso::getCantidad() {
	return this->cantidad;
}

void Recurso::addCantidad(int valor) {
	this->cantidad += valor;
}

void Recurso::removeCantidad(int valor) {
	this->cantidad -= valor;
}

int Recurso::getX() {
	return this->x;
}

int Recurso::getY() {
	return this->y;
}

} /* namespace std */
