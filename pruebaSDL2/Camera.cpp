/*
 * Camera.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: gonzalo
 */

#include "Game.h"
#include "Camera.h"
#include "Vector2D.h"
#include "SDL2/SDL.h"
#include "InputHandler.h"

Camera* Camera::s_pCamera = new Camera();

Camera::Camera() : m_scrollSpeed(3,3), m_direction(0,0), m_margin(30), offsetX(0.0f), offsetY(0.0f)
{
}

void Camera::init()
{
    m_boundY_top = 0;
    m_boundY_bot = TheGame::Instance()->getGameHeight() * 32;//tile height
    m_boundX_left = TheGame::Instance()->getGameWidth() * 32;
    m_boundX_right = TheGame::Instance()->getGameWidth() * (-32);

	m_cameraViewport = { 0, 0, TheGame::Instance()->getGameWidth() , TheGame::Instance()->getGameHeight() }; //posX, posY, width, height
}

bool Camera::isVisible(int mapPosX, int mapPosY)
{
	int leftPos = mapPosX * 64/2 + 32; // *width/2
	int topPos = mapPosY * 32 - 32; //*height
	int botPos = mapPosY * 32 + 32;//*height + height

	int pointX = leftPos - botPos ;
	int pointY = (leftPos + topPos) / 2;

	//
	gameObjectRect = {pointX - offsetX, pointY  - offsetY, 64, 32};

	if (SDL_HasIntersection(&gameObjectRect, &m_cameraViewport))
	{
		return true;
	}
	else {
		return false;
	}
}

void Camera::update()
{
	//actualiza offset de camara
	float dX = m_scrollSpeed.getX() * m_direction.getX();
	float dY = m_scrollSpeed.getY() * m_direction.getY();
	offsetX += dX;
	offsetY += dY;

   /* //Ajusta cámara a los límites
    if(m_cameraViewport.x < m_boundX_left)
    {
    	m_cameraViewport.x = m_boundX_left;
    }
    if( m_cameraViewport.y < m_boundY_bot )
    {
    	m_cameraViewport.y = m_boundY_bot;
    }
    if(m_cameraViewport.x > m_boundX_right)
    {
    	m_cameraViewport.x = m_boundX_right;
    }
    if( m_cameraViewport.y > m_boundY_top )
    {
    	m_cameraViewport.y = m_boundY_top;
    }*/
}

void Camera::handleInput()
{
	float mouseX = TheInputHandler::Instance()->getMousePosition()->getX();
	float mouseY = TheInputHandler::Instance()->getMousePosition()->getY();

	m_direction.setX(0.0f);
	m_direction.setY(0.0f);
	if (mouseX <= m_margin)
		m_direction.setX(-1.0f);

	if (mouseX >= (TheGame::Instance()->getGameWidth() - m_margin))
		m_direction.setX(1.0f);

	if (mouseY <= m_margin)
		m_direction.setY(-1.0f);

	if (mouseY >= (TheGame::Instance()->getGameHeight() - m_margin))
		m_direction.setY(1.0f);

	m_direction.normalize();
}

void Camera::clean()
{
}


