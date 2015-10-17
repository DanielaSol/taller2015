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

void GameObject::load(int screenX, int screenY, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID)
{
	m_mapPosition = Vector2D(screenX, screenY);

	//m_screenPosition = Vector2D(m_mapPosition.m_x * TheGame::Instance()->TILE_WIDTH/2 + TheGame::Instance()->TILE_WIDTH/2,
					//			m_mapPosition.m_y * TheGame::Instance()->TILE_HEIGHT + TheGame::Instance()->TILE_HEIGHT/2);
	m_width = width;
	m_height = height;
	m_destWidth = destWidth;
	m_destHeight = destHeight;
	m_numFrames = numFrames;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
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

