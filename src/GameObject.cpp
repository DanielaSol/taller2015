/*
 * GameObject.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: gonzalo
 */

#include "GameObject.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"

using namespace std;

void GameObject::load(int screenX, int screenY, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID, bool visibility)
{
	m_mapPosition = Vector2D(screenX, screenY);
	m_screenPosition = Vector2D(m_mapPosition.m_x * TheGame::Instance()->TILE_WIDTH/2 + TheGame::Instance()->TILE_WIDTH/2,
								m_mapPosition.m_y * TheGame::Instance()->TILE_HEIGHT + TheGame::Instance()->TILE_HEIGHT/2);
	m_width = width;
	m_height = height;
	m_destWidth = destWidth;
	m_destHeight = destHeight;
	m_numFrames = numFrames;
	m_textureID = textureID;
	m_atSight = visibility;
	m_wasSeen = visibility;
	m_isClicked = false;

	m_currentRow = 1;
	m_currentFrame = 1;

	name = "DEFAULT";
	descripcion = " ";
}

void GameObject::draw()
{
	//Agrega offset de camera y offset de objeto a dibujar

	TheTextureManager::Instance()->drawFrame(m_textureID, m_mapPosition.getX() - TheCamera::Instance()->offsetX - offsetX,
			m_mapPosition.getY()  - TheCamera::Instance()->offsetY - offsetY,
			m_width, m_height,m_destWidth,m_destHeight, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());

}

void GameObject::update()
{
	for(int i = m_mapPosition2.getX() ;i<=m_mapPosition2.getX() + m_ancho;i++)
	{
		for(int j = m_mapPosition2.getY() ; j <= m_mapPosition2.getY() + m_alto;j++){

				if(TheGame::Instance()->unitVision(i,j)){
					m_atSight = true;
				}else if(m_atSight){
					m_wasSeen = true;
					m_atSight = false;
				}
		}
	}

	isClicked();

}

void GameObject::handleInput()
{
}

void GameObject::clean()
{

}

void GameObject::aumentarFrame(){

}

void GameObject::setRow(int row){
	m_currentRow = row;
}

void GameObject::setFrame(int frame){
	m_currentFrame = frame;
}

void GameObject::setOffset(int x, int y){
	offsetX = x;
	offsetY = y;
}

int GameObject::getAlto(){
	return m_alto;
}

int GameObject::getAncho(){
	return m_ancho;
}

void GameObject::setAlto(int alto){
	m_alto = alto;
}

void GameObject::setAncho(int ancho){
	m_ancho = ancho;
}

bool GameObject::positionAtSight(int x,int y){
	return false;
}

void GameObject::setTexture(std::string textureID)
{
	m_textureID = textureID;
}

bool GameObject::operator< (const  GameObject &obj2)
{
	int obj1_value = (int)(*this).m_mapPosition.m_x + (int)(*this).m_mapPosition.m_y;
	int obj2_value = (int)obj2.m_mapPosition.m_x + (int)obj2.m_mapPosition.m_y;

	if ( obj1_value < obj2_value)
		return true;

	if (obj1_value > obj2_value)
		return false;

	if (obj1_value == obj2_value)
	{
		if ((*this).m_mapPosition.m_y <= obj2.m_mapPosition.m_y)
			return true;
		else
			return false;
	}
	return true;
}

void GameObject::isClicked(){

	float posx = TheInputHandler::Instance()->getMousePosition()->getX() + TheCamera::Instance()->offsetX - (TheGame::Instance()->TILE_WIDTH/2);
	float posy = TheInputHandler::Instance()->getMousePosition()->getY() + TheCamera::Instance()->offsetY - (TheGame::Instance()->TILE_WIDTH/2);
	Vector2D* vec = new Vector2D(posx,posy);
	vec->screenToWorld();
	if((m_mapPosition2.getX() == vec->getX())&& (m_mapPosition2.getY() == vec->getY()) && TheInputHandler::Instance()->getMouseButtonState(LEFT)){
		TheGame::Instance()->declick();
		m_isClicked = true;
	}
	delete vec;

}

void GameObject::drawSelected()
{
	float posX = m_mapPosition2.m_x *62/2;
	float posY = m_mapPosition2.m_y *32;

	Vector2D isometricCord2;
	isometricCord2.m_x=posX;
	isometricCord2.m_y=posY;
	isometricCord2.toIsometric();

	TheTextureManager::Instance()->draw("grassSelected", isometricCord2.getX()- TheCamera::Instance()->offsetX , isometricCord2.getY() - TheCamera::Instance()->offsetY,
				100, 50, TheGame::Instance()->getRenderer());

}



