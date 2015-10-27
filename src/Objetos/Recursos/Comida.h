/*
 * Comida.h
 *
 *  Created on: 27/10/2015
 *      Author: daniela
 */

#ifndef COMIDA_H_
#define COMIDA_H_

#include "../../GameObject.h"

class Comida: public GameObject {
public:
	Comida();
	Comida(int x, int y);
	virtual ~Comida();
	void update();

	const int width = 32;
	const int height = 32;
	const int destWidth = 32;
	const int destHeight = 32;
	const int offsetX = 0;
	const int offsetY = 32;
	const int numFrames = 5;
	int row = 7;
	int frame = 7;

};

#endif /* COMIDA_H_ */
