/*
 * Pantalla.h
 *
 *  Created on: 25/10/2015
 *      Author: daniela
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

#include "../SDL_image.h"
#include "SDL2/SDL.h"
#include "Map.h"
#include "../GameObject.h"
#include <map>


using namespace std;

class Pantalla {

public:
	int width;
	int height;

	map<string,SDL_Rect> sectores;

	Pantalla(int width, int height);
	virtual ~Pantalla();
	void clean();

	void draw(SDL_Renderer* m_pRenderer, Map* m_pMap,vector<GameObject*> );
	void init(SDL_Renderer* m_pRenderer);

};


#endif /* PANTALLA_H_ */
