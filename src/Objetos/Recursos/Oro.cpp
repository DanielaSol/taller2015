/*
 * Oro.cpp
 *
 *  Created on: 27/10/2015
 *      Author: daniela
 */

#include "Oro.h"
#include "../../Camera.h"
#include "../../TextureManager.h"
#include "../../Game.h"
#include "../../Utilitarios/Parser.h"

Oro::Oro() {}

Oro::Oro(int x,int y) {
	TheTextureManager::Instance()->load("assets/resources.png","oro", TheGame::Instance()->getRenderer());


	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "oro",false);
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(1);
	GameObject::setAncho(1);

	this->soyRecurso = true;
	this->name = "Oro";
	this->cantidad = 100;
	this->recurso = "Oro";

	delete vec;
}

void Oro::update(){
	GameObject::update();
	if(!m_atSight && m_wasSeen){
		setTexture("oro");
	}else{
		setTexture("oro");
	}
}

void Oro::draw(){
	if (TheCamera::Instance()->isVisible(m_mapPosition2.getX(), m_mapPosition2.getY()))
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, m_mapPosition.getX() - TheCamera::Instance()->offsetX - offsetX + 15,
				m_mapPosition.getY()  - TheCamera::Instance()->offsetY - offsetY - 5,
				m_width, m_height,m_destWidth,m_destHeight, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
}

Oro::~Oro() {
	// TODO Auto-generated destructor stub
}

