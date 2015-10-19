/*
 * Molino.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Molino.h"
#include "Game.h"
#include "TextureManager.h"

Molino::Molino() {
	// TODO Auto-generated constructor stub

}

Molino::Molino(int x,int y){

	TheTextureManager::Instance()->load("assets/windmillSeen.png","molinoSeen", TheGame::Instance()->getRenderer());
	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "molino",false);
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
	GameObject::update();
	if(m_currentFrame == (numFrames-1))
	{
		if(TheParser::Instance()->configGame.objetos.at("molino").animacion.delay != 0)
		{
			delay += 1;
			if(delay > 25*TheParser::Instance()->configGame.objetos.at("molino").animacion.delay) {m_currentFrame = 0; delay = 0;}
		}
		else
		{
			count += TheParser::Instance()->configGame.objetos.at("molino").animacion.fps;
			if (count > 30)
			{
				m_currentFrame = 0;
				count = 0;
			}
		}
	}
	else
	{
		count += TheParser::Instance()->configGame.objetos.at("molino").animacion.fps;
		if (count > 30)
		{
			m_currentFrame += 1;
			count = 0;

		}
		//m_currentFrame = int((( TheParser::Instance()->configGame.objetos.at("molino").animacion.fps ) % m_numFrames));
	}

	if(!m_atSight && m_wasSeen){
			setTexture("molinoSeen");
		}else{
			setTexture("molino");
		}

}
