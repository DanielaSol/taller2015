/*
 * Molino.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Molino.h"
#include "Game.h"

Molino::Molino() {
	// TODO Auto-generated constructor stub

}

Molino::Molino(int x,int y){

	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "molino");
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at("molino").alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at("molino").ancho);
	delete vec;
}

Molino::~Molino() {
	// TODO Auto-generated destructor stub
}

void Molino::update(){

	if(m_currentFrame == 2)
	{
		delay += 1;
		if(delay > 50*TheParser::Instance()->configGame.objetos.at("molino").ancho) {m_currentFrame = 0; delay = 0;}
	}
	else{
	m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
	}

}
