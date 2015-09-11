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
	virtual void aumentarFrame();

	//funciones específicas
	virtual void moveTo (const Vector2D& position);

	Vector2D& getVelocity() { return m_velocity; }
	Vector2D& getDestination() { return m_destination; }
	Vector2D& getDirection() { return m_direction; }

protected:

	Vector2D m_velocity;
	Vector2D m_destination;

private:

	Vector2D m_direction;
	bool m_bChangingDestination; //variable para evitar que el personaje se mueva teniendo apretado click derecho
	bool m_bMoving;
	

	void checkSpriteDirection();

};

#endif /* UNIT_H_ */
