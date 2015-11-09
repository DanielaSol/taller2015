/*
 * Oro.h
 *
 *  Created on: 27/10/2015
 *      Author: daniela
 */

#ifndef ORO_H_
#define ORO_H_

#include "../../GameObject.h"

class Oro: public GameObject {
public:
	Oro();
	Oro(int x, int y);
	virtual ~Oro();
	virtual void update();
	virtual void draw();

	const int width = 32;
	const int height = 32;
	const int destWidth = 32;
	const int destHeight = 32;
	const int offsetX = 0;
	const int offsetY = 32;
	const int numFrames = 10;
	int row = 8;
	int frame = 0;
};

#endif /* ORO_H_ */
