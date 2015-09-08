/*
 * Unit.h
 *
 *  Created on: Sep 7, 2015
 *      Author: gonzalo
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "GameObject.h"
#include "Vector2D.h"

//Clase Padre de las unidades del juego

class Unit: public GameObject
{
public:
	Unit();
	virtual ~Unit(){}

	//funciones básicas
	virtual void load(int x, int y, int width, int height, int numFrames, std::string textureID);
	virtual void draw();
	virtual void update();
	virtual void handleInput();
	virtual void clean();

	//funciones específicas
	virtual void moveTo (Vector2D position);

	Vector2D& getVelocity() { return m_velocity; }
	Vector2D& getDestination() { return m_destination; }
	Vector2D& getDirection() { return m_direction; }

protected:

	Vector2D m_velocity;
	Vector2D m_destination;

private:

	bool m_bChangingDestination;
	Vector2D m_direction;
};

#endif /* UNIT_H_ */
