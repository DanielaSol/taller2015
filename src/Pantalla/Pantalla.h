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
#include "../Utilitarios/Dimensiones.h"


namespace std {

class Pantalla {

public:
	int width;
	int height;

	std::map<std::string,Dimensiones> sectores;



	Pantalla(int width, int height);
	virtual ~Pantalla();

	void draw(SDL_Renderer* m_pRenderer, Map* m_pMap,std::vector<GameObject*> );

};

}
#endif /* PANTALLA_H_ */
