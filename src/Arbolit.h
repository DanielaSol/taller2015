/*
 * Arbolit.h
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#ifndef ARBOLIT_H_
#define ARBOLIT_H_

#include "GameObject.h"

class Arbolit: public GameObject {
public:
	Arbolit();
	Arbolit(int x,int y);
	virtual ~Arbolit();

	virtual void update();

	const int width = 65;
	const int height = 128;
	const int destWidth = 65;
	const int destHeight = 128;
	const int offsetX = 0;
	const int offsetY = 128;
	const int numFrames = 1;
	int row = 8;
	int frame = 2;
};

#endif /* ARBOLIT_H_ */
