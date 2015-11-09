/*
 * Madera.h
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#ifndef MADERA_H_
#define MADERA_H_

#include "../../GameObject.h"

class Madera: public GameObject {
public:
	Madera();
	Madera(int x,int y);
	virtual ~Madera();

	virtual void update();
	virtual void draw();

	const int width = 32;
	const int height = 32;
	const int destWidth = 32;
	const int destHeight = 32;
	const int offsetX = 0;
	const int offsetY = 32;
	const int numFrames = 5;
	int row = 14;
	int frame = 3;
};


#endif /* MADERA_H_ */
