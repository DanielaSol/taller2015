/*
 * Pantalla.cpp
 *
 *  Created on: 25/10/2015
 *      Author: daniela
 */

#include "Pantalla.h"
#include "Map.h"
#include "../GameObject.h"
#include "../TextureManager.h"
#include <map>
#include "../Utilitarios/Dimensiones.h"


namespace std {
Pantalla::Pantalla(int width, int height) {
	this->width = width;
	this->height = height;

	//defino los sectores
	Dimensiones sector;
	sector.x=0;
	sector.y=0;
	sector.width = this->width;
	sector.height = 30;
	sectores.insert( std::pair<string,Dimensiones> ("barra",sector) );

	sector.x=0;
	sector.y=30;
	sector.width = this->width;
	sector.height = this->height - 30 - 200;
	sectores.insert( std::pair<string,Dimensiones> ("mapa",sector) );



}


Pantalla::~Pantalla() {
	// TODO Auto-generated destructor stub
}


void Pantalla::draw(SDL_Renderer* m_pRenderer, Map* m_pMap ,std::vector<GameObject*> entidades) {

	SDL_Rect topLeftViewport;

	Dimensiones sector = sectores.at("barra");
	topLeftViewport.x = sector.x;
	topLeftViewport.y = sector.y;
	topLeftViewport.w = sector.width;
	topLeftViewport.h = sector.height;
	SDL_RenderSetViewport( m_pRenderer, &topLeftViewport );

	TheTextureManager::Instance()->load("assets/wood.jpg","Barra", m_pRenderer);
	SDL_Texture* gTexture= TheTextureManager::Instance()->getTextureMap().at("Barra");
	SDL_RenderCopy( m_pRenderer, gTexture, NULL, NULL );

	sector = sectores.at("mapa");
	topLeftViewport.x = sector.x;
	topLeftViewport.y = sector.y;
	topLeftViewport.w = sector.width;
	topLeftViewport.h = sector.height;
	SDL_RenderSetViewport( m_pRenderer, &topLeftViewport );


	m_pMap->draw();
	 //primero dibuja entidades, luego el personaje (siempre aparece por arriba de las cosas
	for (uint i=0;i<entidades.size();i++){
		if (entidades[i] && (entidades[i]->m_atSight || entidades[i]->m_wasSeen))
			entidades[i]->draw();
	}


	SDL_RenderPresent(m_pRenderer);
}
}
