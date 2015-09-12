
/*Map::Map():
{
}*/

#include "Game.h"
#include "Map.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include <iostream>

using namespace std;

Map::Map():m_mapSize(20,20)
{
	m_tileHandler = new TileHandler();
}
Map::Map(std::string mapName, int mapWidth, int mapHeight)
{
	m_mapName = mapName;
	m_mapSize.setX(mapWidth);
	m_mapSize.setY(mapHeight);

	m_tileHandler = new TileHandler();
}

void Map::load()
{
	m_tileHandler->loadTiles();

	int mapWidth = getMapSize().getX();
	int mapHeight = getMapSize().getY();

	//resize de los vectores del mapa
	mapGrid.resize(mapWidth);
	for (int i = 0; i < mapWidth; ++i)
		mapGrid[i].resize(mapHeight);

	//Inicializa la matriz del mapa con todos 1 (pasto desocupado)
	for(int i = 0 ; i < mapWidth ; i++)
	{
		for(int j = 0 ; j < mapHeight ; j++)
		{
			mapGrid[i][j] = 1; //guarda todos tiles de id 1 (pasto desocupado). Al ser ocupado por un GameObject se tiene que setear el tile en 0
		}
	}
}

void Map::draw()
{
	drawMap();
}

void Map::update(){}
void Map::handleInput(){}

void Map::clean()
{
	int mapWidth = getMapSize().getX();

	for (int i = 0; i < mapWidth; ++i)
		mapGrid[i].clear();
	mapGrid.clear();

	delete m_tileHandler;
}

void Map::drawMap()
{
	int mapWidth = getMapSize().getX();
	int mapHeight = getMapSize().getY();

	//Crea el mapa. Añade el sprite del tile en cada posicion
	for(int i = 0 ; i <  mapWidth; i++)
	{
		for(int j = 0 ; j < mapHeight ; j++)
		{
			placeTile(i, j, mapGrid[i][j]);
		}
	}

	/*for(int i = 0 ; i < 20 ; i++)
	{
		for(int j = 0 ; j < 20 ; j++)
		{
			placeTile(i, j, 0);
		}
	}*/
}

void Map::placeTile(int gridPosX, int gridPosY, int tileID)
{
	float posX = gridPosX * 64 /2;
	float posY = gridPosY * 32;

	Vector2D* isometricCord = new Vector2D(posX, posY);
	isometricCord->toIsometric();

	m_tileHandler->drawTile(tileID, isometricCord->getX(), isometricCord->getY());

	delete isometricCord;


}

