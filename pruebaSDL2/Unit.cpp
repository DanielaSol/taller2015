#include "Unit.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include <math.h>

using namespace std;

Unit::Unit(): GameObject(),
m_velocity(5,5),
m_direction(0,0),
m_bChangingDestination(false),
m_bMoving(false)
{
}

void Unit::load(int x, int y, int width, int height, int numFrames, std::string textureID)
{
    GameObject::load(x, y, width, height, numFrames, textureID);

	m_destination.setX(m_position.getX());
	m_destination.setY(m_position.getY());
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

	GameObject::draw();
}

void Unit::update(){

	//Si no se encuentra donde en la direccion destino asignada, se dirige hacia allá
	if ((m_position.getX() != m_destination.getX()) && (m_position.getY() != m_destination.getY()))
	{
		m_bMoving = true;
		moveTo(m_destination);
	}
	else
	{
		m_bMoving = false;
	}
}

void Unit::moveTo(const Vector2D& position)
{
	//este metodo lo podemos cambiar luego cuando tengamos un movimiento mas complicado.
	//por ahora se dirige en linea recta

	//calcula el vector direccion y lo normaliza (solo lo queremos para indicar dirección de movimiento, no velocidad)
	m_direction.setX(m_destination.getX() - m_position.getX());
	m_direction.setY(m_destination.getY() - m_position.getY());

	m_direction.normalize();

	m_position.m_x += (m_direction.getX() * m_velocity.getX());
	m_position.m_y += (m_direction.getY() * m_velocity.getY());

	//para que no vibre

	float deltaX = m_position.getX() - m_destination.getX();
	float deltaY = m_position.getY() - m_destination.getY();

	if (sqrt(deltaX * deltaX + deltaY * deltaY) <= 5)
	{
		m_position.setX(m_destination.getX());
		m_position.setY(m_destination.getY());
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
			cout << "moving from  x = " <<  m_position.getX() << " y = " << m_position.getY() << " to ---> x = " <<  TheInputHandler::Instance()->getMousePosition()->getX() - (getWidth() / 2.0f) << " y = " << TheInputHandler::Instance()->getMousePosition()->getY() - (getHeight() / 2.0f) << "\n";

			m_bChangingDestination = true; //se me ocurrio, para evitar cambiar posicion si mantiene click derecho apretado

			m_destination.setX(TheInputHandler::Instance()->getMousePosition()->getX() - (getWidth() / 2.0f) );
			m_destination.setY(TheInputHandler::Instance()->getMousePosition()->getY() - (getHeight() / 1.5f) );
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

