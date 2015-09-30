/*
 * Castillo.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Castillo.h"
#include "Parser.h"
#include "Game.h"

Castillo::Castillo() {
	// TODO Auto-generated constructor stub

}

Castillo::Castillo(int x,int y){

	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "castillo");
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at("castillo").alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at("castillo").ancho);
	delete vec;
}

Castillo::~Castillo() {
	// TODO Auto-generated destructor stub
}

