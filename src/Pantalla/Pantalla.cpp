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
#include "../Vector2D.h"

namespace std {
Pantalla::Pantalla(int width, int height) {
	this->width = width;
	this->height = height;

	//defino los sectores
	SDL_Rect sector;
	sector.x=0;
	sector.y=0;
	sector.w = this->width;
	sector.h = 30;
	sectores.insert( std::pair<string,SDL_Rect> ("barra",sector) );

	//mapa
	sector.x=0;
	sector.y=30;
	sector.w = this->width;
	sector.h = this->height - 30 -150;
	sectores.insert( std::pair<string,SDL_Rect> ("mapa",sector) );

	//barra_bajo
	sector.x=0;
	sector.y=this->height -150 ;
	sector.w = 2*(this->width/3);
	sector.h = this->height - 30 ;
	sectores.insert( std::pair<string,SDL_Rect> ("barra_bajo",sector) );

	//minimapa
	sector.x=2*(this->width/3);
	sector.y=this->height -150 ;
	sector.w = 1*(this->width/3);
	sector.h = this->height - 30 ;
	sectores.insert( std::pair<string,SDL_Rect> ("minimapa",sector) );

}


Pantalla::~Pantalla() {
	// TODO Auto-generated destructor stub
}


void Pantalla::draw(SDL_Renderer* m_pRenderer, Map* m_pMap ,std::vector<GameObject*> entidades) {

	SDL_Rect sector;

	//////////////////////////////////////////////////////////////////
	sector = sectores.at("barra");
	TheTextureManager::Instance()->drawArea("barra",sector,m_pRenderer);

	//////////////////////////////////////////////////////////////////
	sector = sectores.at("barra_bajo");
	TheTextureManager::Instance()->drawArea("barra_bajo",sector,m_pRenderer);
	//////////////////////////////////////////////////////////////////
	sector = sectores.at("minimapa");
	TheTextureManager::Instance()->drawArea("minimapa",sector,m_pRenderer);


	for(int i = 0 ; i <  m_pMap->getMapSize().getX(); i++) {
		for(int j = 0 ; j < m_pMap->getMapSize().getY() ; j++) {
			if (m_pMap->getVisionMapValue(i,j) == 1 || m_pMap->getVisionMapValue(i,j) == 2) {
				Vector2D* vector = new Vector2D(0,0);
			    vector->setX(i); vector->setY(j); vector->toIsometric();
			    TheTextureManager::Instance()->drawFrame("punto",vector->getX()+100,vector->getY(),180,150,50,50,1,0,m_pRenderer);
				delete vector;

			}
		}
	}


	//////////////////////////////////////////////////////////////////
	sector = sectores.at("mapa");

	SDL_RenderSetViewport( m_pRenderer, &sector );

	m_pMap->draw();

	 //primero dibuja entidades, luego el personaje (siempre aparece por arriba de las cosas
	for (uint i=0;i<entidades.size();i++){
		if (entidades[i] && (entidades[i]->m_atSight || entidades[i]->m_wasSeen))
			entidades[i]->draw();
	}

	SDL_RenderPresent(m_pRenderer);

}

void Pantalla::init(SDL_Renderer* m_pRenderer) {

	TheTextureManager::Instance()->load("assets/wood.jpg","barra", m_pRenderer);
	TheTextureManager::Instance()->load("assets/paper.png","barra_bajo", m_pRenderer);
	TheTextureManager::Instance()->load("assets/papiro.png","minimapa", m_pRenderer);
	TheTextureManager::Instance()->load("assets/punto.png","punto", m_pRenderer);

}


}
