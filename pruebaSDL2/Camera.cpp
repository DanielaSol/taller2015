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

Camera::Camera() : m_scrollSpeed(10,10), m_direction(0,0), m_scrollMargin(30), offsetX(0.0f), offsetY(0.0f)
{
}

void Camera::init()
{
	//por yaml
	MAX_SCROLLSPEED.setX(10);
	MAX_SCROLLSPEED.setY(10);
	SLOPE_X = MAX_SCROLLSPEED.getX() / (float)m_scrollMargin;
	SLOPE_Y = MAX_SCROLLSPEED.getY() / (float)m_scrollMargin;

    m_boundY_top = - TheGame::Instance()->TILE_HEIGHT;;
    m_boundY_bot = (int)(TheGame::Instance()->getMapHeight() * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameHeight() + TheGame::Instance()->TILE_HEIGHT;//tile height
    m_boundX_left = (int)(TheGame::Instance()->getMapWidth() * -TheGame::Instance()->TILE_HEIGHT);
    m_boundX_right = (int)(TheGame::Instance()->getMapWidth() * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameWidth() +  TheGame::Instance()->TILE_WIDTH;

	m_cameraViewport = { 0, 0, TheGame::Instance()->getGameWidth() , TheGame::Instance()->getGameHeight() }; //posX, posY, width, height
}

bool Camera::isVisible(int mapPosX, int mapPosY)
{
	int leftPos = mapPosX * TheGame::Instance()->TILE_WIDTH/2 + TheGame::Instance()->TILE_WIDTH/2; // *width/2
	int topPos = mapPosY * TheGame::Instance()->TILE_HEIGHT - TheGame::Instance()->TILE_HEIGHT; //*height
	int botPos = mapPosY * TheGame::Instance()->TILE_HEIGHT + TheGame::Instance()->TILE_HEIGHT;//*height + height

	int pointX = leftPos - botPos ;
	int pointY = (leftPos + topPos) / 2;

	//
	gameObjectRect = {pointX - offsetX, pointY  - offsetY, TheGame::Instance()->TILE_WIDTH, TheGame::Instance()->TILE_HEIGHT};

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

    //Ajusta cámara a los límites
    if (offsetX < m_boundX_left)
    {
    	offsetX = m_boundX_left;
    }
    if (offsetY > m_boundY_bot )
    {
    	offsetY = m_boundY_bot;
    }
    if (offsetX > m_boundX_right)
    {
    	offsetX = m_boundX_right;
    }
    if (offsetY < m_boundY_top )
    {
    	offsetY = m_boundY_top;
    }
}

void Camera::handleInput()
{
	float mouseX = TheInputHandler::Instance()->getMousePosition()->getX();
	float mouseY = TheInputHandler::Instance()->getMousePosition()->getY();

	m_direction.setX(0.0f);
	m_direction.setY(0.0f);

	if (mouseX <= m_scrollMargin)
	{
		m_direction.setX(-1.0f);
		m_scrollSpeed.setX ( MAX_SCROLLSPEED.getX() - (SLOPE_X * mouseX));
	}

	if (mouseX >= (TheGame::Instance()->getGameWidth() - m_scrollMargin))
	{
		m_direction.setX(1.0f);
		m_scrollSpeed.setX ( MAX_SCROLLSPEED.getX() - (SLOPE_X * (TheGame::Instance()->getGameWidth() - mouseX)));
	}

	if (mouseY <= m_scrollMargin)
	{
		m_direction.setY(-1.0f);
		m_scrollSpeed.setY ( MAX_SCROLLSPEED.getY() - (SLOPE_Y * mouseY));
	}

	if (mouseY >= (TheGame::Instance()->getGameHeight() - m_scrollMargin))
	{
		m_direction.setY(1.0f);
		m_scrollSpeed.setY ( MAX_SCROLLSPEED.getY() - (SLOPE_Y * (TheGame::Instance()->getGameHeight() - mouseY)));
	}

	m_direction.normalize();
}

void Camera::clean()
{
}
