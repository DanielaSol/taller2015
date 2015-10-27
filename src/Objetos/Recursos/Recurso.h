/*
 * Recurso.h
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#ifndef RECURSO_H_
#define RECURSO_H_

namespace std {

class Recurso {
protected:
	int cantidad;
	int x;
	int y;

public:
	Recurso();
	virtual ~Recurso();
	int getCantidad();
	void addCantidad(int valor);
	void removeCantidad(int valor);
	int getX();
	int getY();

};

} /* namespace std */
#endif /* RECURSO_H_ */
