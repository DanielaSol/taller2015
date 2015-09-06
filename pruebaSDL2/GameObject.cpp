/*
 * GameObject.cpp
 *
 *  Created on: 05/09/2015
 *      Author: facundo
 */

#include "GameObject.h"


void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;
	speed = 1;
	posicionFinalx = x;
	posicionFinaly = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
}

void GameObject::draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y,
					m_width, m_height, m_currentRow, m_currentFrame, pRenderer);
}

void GameObject::update()
{
	if(posicionFinalx != m_x){
		if(posicionFinalx > m_x){
			m_x += speed;
		}else{
			m_x -= speed;
		}
	}
	if(posicionFinaly != m_y){
		if(posicionFinaly > m_y){
			m_y += speed;
		}else{
			m_y -= speed;
		}
	}
}

void GameObject::aumentarPosDer(){

	//m_x -= 1;
}

void GameObject::click(int mousex,int mousey){

	posicionFinalx = mousex;
	posicionFinaly = mousey;

}
