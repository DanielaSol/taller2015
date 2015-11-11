/*
 * Castillo.cpp
 *
 *  Created on: 30/09/2015
 *      Author: facundo
 */

#include "Castillo.h"
#include "../../Utilitarios/Parser.h"
#include "../../Game.h"
#include "../../TextureManager.h"
#include "../../Camera.h"

Castillo::Castillo() {
	// TODO Auto-generated constructor stub

}

Castillo::Castillo(int x,int y){

	/*if (TheTextureManager::Instance()->getTextureMap().count("castilloSeen") == 0) {
		TheTextureManager::Instance()->load("assets/castilloSeen.png","castilloSeen", TheGame::Instance()->getRenderer());
	}
	//float possx = x * TheGame::TILE_WIDTH/2;
	//float possy = y * TheGame::TILE_HEIGHT;
	Vector2D* vec = new Vector2D(x, y);
	vec->worldToScreen();
	//offset hardcodeado de la imagen
	vec->m_x += 15;
	vec->m_y += 70;
	//vec->setX(possx);
	//vec->setY(possy);
	//vec->toIsometric();

	GameObject::load( vec->getX(), vec->getY(),  width, height, destWidth, destHeight, numFrames, "castillo",false);
	m_mapPosition2.setX(x);
	m_mapPosition2.setY(y);
	GameObject::setFrame(frame);
	GameObject::setOffset(offsetX,offsetY);
	GameObject::setRow(row);
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at("castillo").alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at("castillo").ancho);
	name = "Castillo";
	delete vec;*/


	if (TheTextureManager::Instance()->getTextureMap().count("castilloSeen") == 0) {
		TheTextureManager::Instance()->load("assets/castilloSeen.png","castilloSeen", TheGame::Instance()->getRenderer());
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
	GameObject::setAlto(TheParser::Instance()->configGame.objetos.at("castillo").alto);
	GameObject::setAncho(TheParser::Instance()->configGame.objetos.at("castillo").ancho);
	name = "CASA";
	description= "UNA CASA ES UNA CONSTRUCCION";
	delete vec;
}

Castillo::~Castillo() {
	// TODO Auto-generated destructor stub
}

void Castillo::update(){
	GameObject::update();
	if(!m_atSight && m_wasSeen){
		setTexture("castilloSeen");
	}else{
		setTexture("castillo");
	}
}


void Castillo::drawSelected()
{
	float posX = m_mapPosition2.m_x *64/2;
	float posY = m_mapPosition2.m_y *32;

	Vector2D isometricCord2;
	isometricCord2.m_x=posX;
	isometricCord2.m_y=posY;
	isometricCord2.toIsometric();

	TheTextureManager::Instance()->draw("grassSelected", isometricCord2.getX()- TheCamera::Instance()->offsetX-50 , isometricCord2.getY() - TheCamera::Instance()->offsetY-50,
				160, 100, TheGame::Instance()->getRenderer());

}
