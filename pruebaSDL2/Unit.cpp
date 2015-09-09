#include "Unit.h"
#include "InputHandler.h"
#include <iostream>
#include <math.h>

using namespace std;

Unit::Unit(): GameObject(),
m_velocity(5,5),
m_direction(0,0),
m_bChangingDestination(false)
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
	//nada especial
    GameObject::draw();
}

void Unit::update(){

	//Si no se encuentra donde en la direccion destino asignada, se dirige hacia allá
	if ((m_position.getX() != m_destination.getX()) && (m_position.getY() != m_destination.getY()))
	{
		moveTo(m_destination);
	}
}

void Unit::moveTo(Vector2D position)
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

	if (sqrt(deltaX * deltaX + deltaY * deltaY) <= 2.1)
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
			cout << "moving to " <<  m_destination.getX() << "/" << m_destination.getY()<< "\n";
			m_bChangingDestination = true; //se me ocurrio, para evitar cambiar posicion si mantiene click derecho apretado
			m_destination.setX(TheInputHandler::Instance()->getMousePosition()->getX() - (getWidth() / 2.0f) );
			m_destination.setY(TheInputHandler::Instance()->getMousePosition()->getY() - (getHeight() / 2.0f) );
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
