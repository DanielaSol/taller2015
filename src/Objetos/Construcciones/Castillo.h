/*
 * Castillo.h
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#ifndef CASTILLO_H_
#define CASTILLO_H_

#include "../../GameObject.h"

class Castillo: public GameObject {
public:
	Castillo();
	Castillo(int x,int y);
	virtual ~Castillo();

	void update();

	void drawSelected();

	const int width = 192;
	const int height = 224;
	const int destWidth = 130;
	const int destHeight = 151;
	const int offsetX = 130/4;
	const int offsetY = 151;
	const int numFrames = 1;
	int row = 1;
	int frame = 0;
};

#endif /* CASTILLO_H_ */
