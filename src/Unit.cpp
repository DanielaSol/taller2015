#include "Unit.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Parser.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <math.h>

using namespace std;

Unit::Unit(): GameObject(),
m_velocity(TheParser::Instance()->configGame.configuracion.vel_personaje,
			TheParser::Instance()->configGame.configuracion.vel_personaje),
m_direction(0,0),
m_bChangingDestination(false),
m_bMoving(false)
{
}

void Unit::load(int x, int y, int width, int height,int destWidth, int destHeight, int numFrames, std::string textureID)
{
    GameObject::load(x, y, width, height, destWidth, destHeight, numFrames, textureID);

    //
	//m_destination.setX(m_screenPosition.getX());
	//m_destination.setY(m_screenPosition.getY());
}

void Unit::draw()
{
	// Esta funcion en realidad deberia estar implementada en gameObject ya que todos los personajes
	// van a tener la misma funcionalidad para moverse.

	if (m_bMoving)
	{
		aumentarFrame();
		checkSpriteDirection();
	}
	TheTextureManager::Instance()->drawFrame(m_textureID, m_screenPosition.getX() - TheCamera::Instance()->offsetX - m_destWidth/2,
												m_screenPosition.getY()  - TheCamera::Instance()->offsetY - m_destHeight/1.5f,
												m_width, m_height,m_destWidth,m_destHeight, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());

}

void Unit::update(){

	GameObject::update();
	//Si no se encuentra donde en la direccion destino asignada, se dirige hacia allá
	if ((m_bMoving) && (((m_mapPosition.getX() != m_destination.getX()) || (m_mapPosition.getY() != m_destination.getY()))))
	{
		moveTo(m_destination);
	}
	else
	{
		m_bMoving = false;
	}
}

void Unit::moveTo(const Vector2D& position)
{
	//calcula posicion actual
	m_mapPosition.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/4);
	m_mapPosition.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/4);
	m_mapPosition.toCartesian();
	m_mapPosition.setX((int)(m_mapPosition.getX() / TheGame::Instance()->TILE_WIDTH*2));
	m_mapPosition.setY((int)(m_mapPosition.getY() / TheGame::Instance()->TILE_HEIGHT));
	m_mapPosition2.setX(m_screenPosition.getX() - TheGame::Instance()->TILE_WIDTH/4);
		m_mapPosition2.setY(m_screenPosition.getY() - TheGame::Instance()->TILE_HEIGHT/4);
		m_mapPosition2.toCartesian();
		m_mapPosition2.setX((int)(m_mapPosition.getX() / TheGame::Instance()->TILE_WIDTH*2));
		m_mapPosition2.setY((int)(m_mapPosition.getY() / TheGame::Instance()->TILE_HEIGHT));


	//calcula el vector direccion y lo normaliza (solo lo queremos para indicar dirección de movimiento, no velocidad)
	m_direction.setX(m_screenCoordDestination.getX() - m_screenPosition.getX());
	m_direction.setY(m_screenCoordDestination.getY() - m_screenPosition.getY());
	m_direction.normalize();

	//clamp
	float nextPositionX = m_screenPosition.m_x + (m_direction.getX() * m_velocity.getX());
	float nextPositionY = m_screenPosition.m_y + (m_direction.getY() * m_velocity.getY());
	if ((((m_screenPosition.m_x < m_screenCoordDestination.m_x) && (nextPositionX >= m_screenCoordDestination.m_x )) ||
		((m_screenPosition.m_x > m_screenCoordDestination.m_x) && (nextPositionX <= m_screenCoordDestination.m_x ))) &&
		(((m_screenPosition.m_y < m_screenCoordDestination.m_y) && (nextPositionY >= m_screenCoordDestination.m_y )) ||
		((m_screenPosition.m_y > m_screenCoordDestination.m_y) && (nextPositionY <= m_screenCoordDestination.m_y ))))
	{
		m_screenPosition.m_x = m_screenCoordDestination.m_x;
		m_screenPosition.m_y = m_screenCoordDestination.m_y;
	}
	else
	{
		//mueve al personaje
		m_screenPosition.m_x += (m_direction.getX() * m_velocity.getX());
		m_screenPosition.m_y += (m_direction.getY() * m_velocity.getY());
	}

}

void Unit::handleInput()
{
	// deberia checkear tambien si la unidad está seleccionada. La variable isSelected la puse en GameObject, ya que consideré que
	// se puede apretar en cualquier objeto, como en el age.

	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		if (!m_bChangingDestination)
		{
			//El siguiente cout no informa errores (no es necesario ponerlo en el log) y es bastante costoso. Lo podemos sacar
			//cout << "moving from  x = " <<  m_screenPosition.getX() << " y = " << m_screenPosition.getY() << " to ---> x = " <<  TheInputHandler::Instance()->getMousePosition()->getX() - (getWidth() / 2.0f) << " y = " << TheInputHandler::Instance()->getMousePosition()->getY() - (getHeight() / 2.0f) << "\n";

			float backUpScreenX = m_screenCoordDestination.getX();
			float backUpScreenY = m_screenCoordDestination.getY();
			float backUpCarterianX = m_destination.getX();
			float backUpCarterianY = m_destination.getY();

			//Calcula la coordenada a moverse en coordenadas cartesianas de mapa
			float coordX = (TheInputHandler::Instance()->getMousePosition()->getX() + TheCamera::Instance()->offsetX);
			float coordY = (TheInputHandler::Instance()->getMousePosition()->getY() + TheCamera::Instance()->offsetY);
			m_screenCoordDestination.setX(coordX);
			m_screenCoordDestination.setY(coordY);
			m_destination.setX(coordX  - TheGame::Instance()->TILE_WIDTH/4);
			m_destination.setY(coordY  - TheGame::Instance()->TILE_HEIGHT/4);
			m_destination.toCartesian();
			m_destination.setX((int)(m_destination.getX() / TheGame::Instance()->TILE_WIDTH*2));
			m_destination.setY((int)(m_destination.getY() / TheGame::Instance()->TILE_HEIGHT));
			cout << "Tile clicked = ( " << (int) m_destination.m_x << " , " << (int)m_destination.m_y << " ) \n";

			//analiza que no se cliquee fuera de los bordes
			if ((m_destination.getX() >= TheGame::Instance()->getMapWidth()) ||
					(m_destination.getY() >= TheGame::Instance()->getMapHeight())||
					(m_destination.getX() < 0) ||
					(m_destination.getY() < 0))
			{
				//revierte en caso positivo
				m_bChangingDestination = false;
				m_destination.setX(backUpCarterianX);
				m_destination.setY(backUpCarterianY);
				m_screenCoordDestination.setX(backUpScreenX);
				m_screenCoordDestination.setY(backUpScreenY);
				return;
			}

			m_bChangingDestination = true; //se me ocurrio, para evitar cambiar posicion si mantiene click derecho apretado
			m_bMoving = true;

		}
	}
	else
	{
		m_bChangingDestination = false;
	}
}

void Unit::clean(){

	//nada especial
    GameObject::clean();
}

void Unit::aumentarFrame(){

	m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

	/*m_currentFrame += 1;

	if(m_currentFrame > m_numFrames)
	{
		m_currentFrame = 1;
	}*/
}

void Unit::checkSpriteDirection()
{
	//se esta moviendo y es hacia abajo
	if(m_direction.getY() > 0.4f)
	{
		//abajo a la derecha
		if(m_direction.getX() > 0.4f)
		{
			m_currentRow = 8;
		}
		//abajo a la izquierda
		else if(m_direction.getX() < -0.4f)
		{
			m_currentRow = 2;
		}
		//abajo exclusivo
		else
		{
			m_currentRow = 1;
		}
	}
	//se esta moviendo y es hacia arriba
	else if(m_direction.getY() < -0.4)
	{
		//arriba a la derecha
		if(m_direction.getX() > 0.4)
		{
			m_currentRow = 6;
		}
		//arriba a la izquierda
		else if(m_direction.getX() < -0.4)
		{
			m_currentRow = 4;
		}
		//arriba exclusivo
		else
		{
			m_currentRow = 5;
		}
	}
	// se mueve hacia la izquierda o derecha exclusivamente
	else
	{
		//derecha
		if(m_direction.getX() > 0){
			m_currentRow = 7;
		}
		else
		{
			m_currentRow = 3;
		}
	}
}

