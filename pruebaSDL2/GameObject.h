/*
 * GameObject.h
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "TextureManager.h"

class GameObject {

public:
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean() { std::cout << "clean game object"; }
	void aumentarPosDer();
	void click(int,int);

protected:
	std::string m_textureID;
	int m_currentFrame;
	int m_currentRow;
	int m_x;
	int m_y;
	int speed;
	int m_width;
	int m_height;
	int posicionFinalx;
	int posicionFinaly;

};

#endif /* GAMEOBJECT_H_ */
