#ifndef MAP_H_
#define MAP_H_

#include "Vector2D.h"
#include "TileHandler.h"
#include "GameObject.h"

#include <vector>
#include <string>
#include <string>


class Map
{
friend class MapSearchNode;
public:
	Map();
	Map(std::string mapName, int mapWidth, int mapHeight);

	//funciones básicas
	void load();
	void draw();
	void update();
	void handleInput();
	void clean();
	void setValue(int,int,int);
	int getValue(int,int);
	int getVisionMapValue(int,int);

	std::string getName() { return m_mapName; }
	Vector2D& getMapSize() { return m_mapSize; }

	void drawMap();

	void placeTile(int gridPosX, int gridPosY, int tileID);


private:

	std::string m_mapName;
	Vector2D m_mapSize;

	std::vector< std::vector<int> >  m_mapGrid;
	std::vector< std::vector<int> >  m_mapGrid2;
	TileHandler* m_pTileHandler;

	Vector2D* isometricCord; //temp buffer


};



#endif /* MAP_H_ */
