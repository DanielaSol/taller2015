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
#include "Parser.h"

//Camera* Camera::s_pCamera = new Camera();
Camera* Camera::s_pCamera;

Camera::Camera() : m_scrollSpeed(30,30),m_scrollMargin(TheParser::Instance()->configGame.configuracion.margen_scroll), m_direction(0,0), offsetX(0.0f), offsetY(0.0f)
{
	// CAMBIAR TMB EN RESET m_scrollMargin = TheParser::Instance()->configGame.configuracion.margen_scroll;
  //  cout << TheParser::Instance()->configGame.configuracion.margen_scroll << endl;

}

void Camera::init()
{
	m_scrollMargin = TheParser::Instance()->configGame.configuracion.margen_scroll;
	//por yaml
	MAX_SCROLLSPEED.setX(15);
	MAX_SCROLLSPEED.setY(15);
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
	//dY la calcula como una una f(x)

	//límites diagonales
	//límite superior derecho
	if (offsetY + dY < offsetX/2)
	{
		dY = offsetX/2 - offsetY;
	}

	//limite superior izquierdo
	if (offsetY + dY < -(offsetX + TheGame::Instance()->getGameWidth())/2)
		dY = -(offsetX + TheGame::Instance()->getGameWidth())/2 - offsetY;

	//limite inferior izquierdo
	if (offsetY + dY > offsetX/2  + (100 * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameWidth()/4)
		dY = offsetX/2  + (100 * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameWidth()/4 - offsetY;

	//limite inferior derecho
	if (offsetY + dY > -(offsetX + TheGame::Instance()->getGameWidth())/2 + (TheGame::Instance()->getMapHeight() * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameHeight()/4)
		dY = -(offsetX + TheGame::Instance()->getGameWidth())/2 - offsetY + (TheGame::Instance()->getMapHeight() * TheGame::Instance()->TILE_HEIGHT) - TheGame::Instance()->getGameHeight()/4;

	offsetY += dY;
    //Ajusta cámara a los otros límites
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

const Vector2D Camera::TranslateToWorldCoordinates(int screenX, int screenY) //NO USAR, ME ESTABA DANDO MAL Y LA ABANDONE
{
	buffer.setX(screenX);
	buffer.setY(screenY);
	buffer.setX(screenX  - TheGame::Instance()->TILE_WIDTH/4);
	buffer.setY(screenY  - TheGame::Instance()->TILE_HEIGHT/4);
	buffer.toCartesian();
	buffer.setX((int)(buffer.getX() / TheGame::Instance()->TILE_WIDTH*2));
	buffer.setY((int)(buffer.getY() / TheGame::Instance()->TILE_HEIGHT));

	return buffer;
}

void Camera::reset()
{
	offsetX = 0;
	offsetY = 0;
	//por yaml
	init();
	//m_scrollMargin = TheParser::Instance()->configGame.configuracion.margen_scroll;
}

void Camera::clean()
{
}
