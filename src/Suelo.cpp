/*
 * Suelo.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Suelo.h"
#include "Parser.h"
#include "Game.h"

Suelo::Suelo() {
	// TODO Auto-generated constructor stub

}

Suelo::Suelo(int x,int y,std::string tipo){

	float possx = (x) * TheGame::TILE_WIDTH/2;
	float possy = (y) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, tipo,false);
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at(tipo).alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at(tipo).ancho);
	delete vec;
}

Suelo::~Suelo() {
	// TODO Auto-generated destructor stub
}

