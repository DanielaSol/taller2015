/*
 * Arbolit.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Arbolit.h"
#include "../Utilitarios/Parser.h"
#include "../Game.h"
#include "../TextureManager.h"

Arbolit::Arbolit() {
	// TODO Auto-generated constructor stub

}

Arbolit::Arbolit(int x,int y){

	if (TheTextureManager::Instance()->getTextureMap().count("arbolSeen") == 0) {
		TheTextureManager::Instance()->load("assets/terrainSeen.png","arbolSeen", TheGame::Instance()->getRenderer());
	}

	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "arbol",false);
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at("arbol").alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at("arbol").ancho);
	name="ARBOL";
	descripcion = "LOS ARBOLES SON OBSTACULOS EN EL JUEGO";
	interactuable = true;
	cantidad = 100;
	recurso ="Madera";
	delete vec;

}

Arbolit::~Arbolit() {
	// TODO Auto-generated destructor stub
}



void Arbolit::update(){
	GameObject::update();
	if(!m_atSight && m_wasSeen){
		setTexture("arbolSeen");
	}else{
		setTexture("arbol");
	}
}


