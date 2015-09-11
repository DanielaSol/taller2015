#ifndef MAP_H_
#define MAP_H_

#include "Vector2D.h"
#include <string>

#include "GameObject.h"

class Map
{
public:
	//Map();
	virtual ~Map(){}

	//funciones básicas
	void load();
	void draw();
	void update();
	void handleInput();
	void clean();

	std::string getName() { return m_mapName; }
	Vector2D& getMapSize() { return m_mapSize; }

	void generateMap();

	void placeTile(int gridPosX, int gridPosY, int tileID);

	//int[TileMetadata][TileMetadata] mapGrid;

private:

	std::string m_mapName;
	Vector2D m_mapSize;

	struct TileMetadata{ // NO SE, ESTABA PROBANDO
		int tileID;
		GameObject* point;
	};

};



#endif /* MAP_H_ */
