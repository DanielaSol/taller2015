/*
 * Madera.cpp
 *
 *  Created on: 26/10/2015
 *      Author: daniela
 */

#include "Madera.h"
#include "../../Camera.h"
#include "../../TextureManager.h"
#include "../../Game.h"
#include "../../Utilitarios/Parser.h"

Madera::Madera() {
}

Madera::Madera(int x,int y) {

	//if (TheTextureManager::Instance()->getTextureMap().count("madera") == 0) {
		TheTextureManager::Instance()->load("assets/resources.png","madera", TheGame::Instance()->getRenderer());
	//}

	float possx = (x+1) * TheGame::TILE_WIDTH/2;
	float possy = (y+1) * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(0,0);
	vec->setX(possx);
	vec->setY(possy);
	vec->toIsometric();
	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "madera",false);
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(1);
	GameObject::setAncho(1);

	this->recurso = true;
	this->name = "Madera";
	this->cantidad = 1;

	delete vec;
}

Madera::~Madera() {
	// TODO Auto-generated destructor stub
}

void Madera::update(){
	GameObject::update();
	if(!m_atSight && m_wasSeen){
		setTexture("madera");
	}else{
		setTexture("madera");
	}
}

void Madera::draw(){
	if (TheCamera::Instance()->isVisible(m_mapPosition2.getX(), m_mapPosition2.getY()))
	{
		TheTextureManager::Instance()->drawFrame(m_textureID, m_mapPosition.getX() - TheCamera::Instance()->offsetX - offsetX + 15,
				m_mapPosition.getY()  - TheCamera::Instance()->offsetY - offsetY,
				m_width, m_height,m_destWidth,m_destHeight, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
}


