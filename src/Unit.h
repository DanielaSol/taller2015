#ifndef UNIT_H_
#define UNIT_H_

#include "Astar/MapSearchNode.h"
#include "Astar/stlastar.h"
#include "GameObject.h"
#include "Vector2D.h"

//Clase Padre de las unidades del juego
class Unit: public GameObject
{
public:
	Unit();
	virtual ~Unit(){}

	//funciones básicas
	virtual void load(int x, int y, int width, int height,int destWidth,int destHeight, int numFrames, std::string textureID,bool visibility);
	virtual void draw();
	virtual void update();
	virtual void handleInput();
	virtual void clean();
	virtual void aumentarFrame();

	//funciones específicas
	virtual void moveTo (const Vector2D& position);

	bool positionAtSight(int,int);

	Vector2D& getVelocity() { return m_velocity; }
	Vector2D& getDestination() { return m_destination; }
	Vector2D& getDirection() { return m_direction; }

	int m_vision;

protected:

	Vector2D m_velocity;
	Vector2D m_destination;
	Vector2D m_lastMapPosition;

	bool teniaQueInteractuar;
	Vector2D interactuarCon;


private:

	Vector2D m_direction;
	Vector2D m_screenCoordDestination;

	AStarSearch<MapSearchNode> astarsearch;
	MapSearchNode *m_node;

	bool m_bChangingDestination; //variable para evitar que el personaje se mueva teniendo apretado click derecho
	bool m_bMoving;

	void checkSpriteDirection();
	void occupyTile(const Vector2D& newPosition);
	bool calculatePath(Vector2D destination);

};

#endif /* UNIT_H_ */
