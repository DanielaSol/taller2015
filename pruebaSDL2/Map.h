#ifndef MAP_H_
#define MAP_H_

#include "Vector2D.h"
#include <string>

#include "GameObject.h"
#include <vector>
#include <string>
#include "TileHandler.h"

class Map
{
friend class GameObject;

public:
	Map();
	Map(std::string mapName, int mapWidth, int mapHeight);

	//funciones básicas
	void load();
	void draw();
	void update();
	void handleInput();
	void clean();

	std::string getName() { return m_mapName; }
	Vector2D& getMapSize() { return m_mapSize; }

	void drawMap();

	void placeTile(int gridPosX, int gridPosY, int tileID);


private:

	std::string m_mapName;
	Vector2D m_mapSize;

	std::vector< std::vector<int> >  m_mapGrid;

	TileHandler* m_pTileHandler;

	Vector2D* isometricCord; //temp buffer


};



#endif /* MAP_H_ */
