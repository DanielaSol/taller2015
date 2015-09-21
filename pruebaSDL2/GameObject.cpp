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

void GameObject::load(int x, int y, int width, int height, int numFrames, std::string textureID)
{
	m_mapPosition = Vector2D(0,0);
	m_screenPosition = Vector2D(m_mapPosition.m_x * TheGame::Instance()->TILE_WIDTH/2 - TheGame::Instance()->TILE_WIDTH/2 - width/2,
								m_mapPosition.m_y * TheGame::Instance()->TILE_HEIGHT - TheGame::Instance()->TILE_HEIGHT/2 - height/2);
	m_width = width;
	m_height = height;
	m_numFrames = numFrames;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
}

void GameObject::draw()
{
	//Agrega offset de camera
	TheTextureManager::Instance()->drawFrame(m_textureID, m_screenPosition.getX() - TheCamera::Instance()->offsetX - m_width/2,
											m_screenPosition.getY()  - TheCamera::Instance()->offsetY - m_height/1.5f,
											m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
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
