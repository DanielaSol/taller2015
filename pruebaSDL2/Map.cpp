
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

/*Map::Map():
{
}
Map::~Map():
{
}*/

void Map::load()
{
	TheTextureManager::Instance()->load("assets/Tiles/Grass.png","grassTile", TheGame::Instance()->getRenderer());
}

void Map::draw()
{
	generateMap();
}
void Map::update(){}
void Map::handleInput(){}
void Map::clean(){}

void Map::generateMap()
{
	for(int i = 0 ; i < 20 ; i++)
	{
		for(int j = 0 ; j < 20 ; j++)
		{
			placeTile(i, j, 0);
		}
	}

}

void Map::placeTile(int gridPosX, int gridPosY, int tileID)
{
	float posX = gridPosX * 64 /2;
	float posY = gridPosY * 32;

	Vector2D* isometricCord = new Vector2D(posX, posY);
	isometricCord->toIsometric();

	TheTextureManager::Instance()->draw("grassTile", isometricCord->getX(), isometricCord->getY(),
					64, 32, TheGame::Instance()->getRenderer());
	delete isometricCord;


}

