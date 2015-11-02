
/*Map::Map():
{
}*/

#include "../Game.h"
#include "Map.h"
#include "../TextureManager.h"
#include "../InputHandler.h"
#include "../Vector2D.h"
#include "../Camera.h"
#include <math.h>
#include <iostream>

using namespace std;

Map::Map():m_mapSize(100,100)
{
	m_pTileHandler = new TileHandler();
	isometricCord = new Vector2D(0,0);
}
Map::Map(std::string mapName, int mapWidth, int mapHeight)
{
	m_mapName = mapName;
	m_mapSize.setX(mapWidth);
	m_mapSize.setY(mapHeight);

	m_pTileHandler = new TileHandler();
	isometricCord = new Vector2D(0,0);
}

void Map::load()
{
	m_pTileHandler->loadTiles();

	int mapWidth = getMapSize().getX();
	int mapHeight = getMapSize().getY();

	//resize de los vectores del mapa
	m_mapGrid.resize(mapWidth);
	m_mapGrid2.resize(mapWidth);
	for (int i = 0; i < mapWidth; ++i)
	{
		m_mapGrid[i].resize(mapHeight);
		m_mapGrid2[i].resize(mapHeight);
	}

	//Inicializa la matriz del mapa con todos 1 (pasto desocupado)
	for(int i = 0 ; i < mapWidth ; i++)
	{
		for(int j = 0 ; j < mapHeight ; j++)
		{
			m_mapGrid[i][j] = 1; //guarda todos tiles de id 1 (pasto desocupado). Al ser ocupado por un GameObject se tiene que setear el tile en 0
			m_mapGrid2[i][j] = 0; // 0: no visto. 1: esta siendo visto. 2: fue visto
		}
	}

}

void Map::draw()
{
	drawMap();
}

void Map::update()
{
	int mapWidth = getMapSize().getX();
		int mapHeight = getMapSize().getY();

		for(int i = 0 ; i <  mapWidth; i++)
		{
			for(int j = 0 ; j < mapHeight ; j++)
			{
				if(TheGame::Instance()->unitVision(i,j)){
					m_mapGrid2[i][j] = 1;
				}
				else if(m_mapGrid2[i][j] == 1){
					m_mapGrid2[i][j] = 2;
				}
			}
		}

}
void Map::handleInput(){}

void Map::clean()
{
	int mapWidth = getMapSize().getX();

	for (int i = 0; i < mapWidth; ++i)
		m_mapGrid[i].clear();
	m_mapGrid.clear();

	delete m_pTileHandler;
	delete 	isometricCord;
}

void Map::drawMap()
{
	int mapWidth = getMapSize().getX();
	int mapHeight = getMapSize().getY();

	/*int fromX = abs(TheCamera::Instance()->m_cameraViewport.x / 32);
	int toX = abs(TheCamera::Instance()->m_cameraViewport.x / 32) + TheCamera::Instance()->m_cameraViewport.w;*/

	//Crea el mapa. Añade el sprite del tile en cada posicion
	for(int i = 0 ; i <  mapWidth; i++)
	{
		for(int j = 0 ; j < mapHeight ; j++)
		{
			if (TheCamera::Instance()->isVisible(i,j))
				placeTile(i, j, m_mapGrid2[i][j]);
		}
	}

}

void Map::placeTile(int gridPosX, int gridPosY, int tileID)
{
	float posX = gridPosX * 64 /2 ;
	float posY = gridPosY * 32 ;

	isometricCord->setX(posX);
	isometricCord->setY(posY);
	isometricCord->toIsometric();

	m_pTileHandler->drawTile(tileID, isometricCord->getX()- TheCamera::Instance()->offsetX, isometricCord->getY()- TheCamera::Instance()->offsetY);

}

void Map::setValue(int x, int y,int valor){

	m_mapGrid[x][y] = valor;
}

int Map::getValue(int x, int y){

	return m_mapGrid[x][y];

}

int Map::getVisionMapValue(int x,int y){

	return m_mapGrid2[x][y];
}

