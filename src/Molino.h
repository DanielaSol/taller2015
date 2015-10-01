/*
 * Molino.h
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#ifndef MOLINO_H_
#define MOLINO_H_

#include "GameObject.h"
#include "Parser.h"

class Molino: public GameObject {
public:
	Molino();
	Molino(int x,int y);
	virtual ~Molino();

	virtual void update();

	const int width = 59;
	const int height = 102;
	const int destWidth = 59;
	const int destHeight = 102;
	const int offsetX = 0;
	const int offsetY = 102;
	const int numFrames = 3;
	int delay = 0;
	int row = 1;
	int frame = 0;

	int count = 0;

};

#endif /* MOLINO_H_ */
