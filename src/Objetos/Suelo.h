/*
 * Suelo.h
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#ifndef SUELO_H_
#define SUELO_H_

#include "../GameObject.h"

class Suelo: public GameObject {
public:
	Suelo();
	Suelo(int x,int y, std::string tipo);
	virtual ~Suelo();

	const int width = 64;
	const int height = 32;
	const int destWidth = 64;
	const int destHeight = 32;
	const int offsetX = 0;
	const int offsetY = 0;
	const int numFrames = 1;
	int row = 1;
	int frame = 0;

};

#endif /* SUELO_H_ */
