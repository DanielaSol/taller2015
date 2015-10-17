/* TILES ID
 *  0 = OCUPADA PASTO
 *  1 = PASTO
 *
 *  2 = AGUA BAJA CAMINABLE
 *  3 = AGUA BAJA OCUPADA
 *  4 = AGUA PROFUNDA
 *  etcetera, se entiende la idea
 */
#include "TileHandler.h"
#include <string>
#include "Game.h"
#include "TextureManager.h"

TileHandler::TileHandler(): m_tileWidth(64),m_tileHeight(32){}

void TileHandler::loadTiles()
{
	TheTextureManager::Instance()->load("assets/Tiles/Grass.png","grassTile", TheGame::Instance()->getRenderer());
}

void TileHandler::drawTile(int tileID, int isoX, int isoY)
{
	switch (tileID)
	{
	case 0: TheTextureManager::Instance()->draw("grassTile", isoX, isoY,
			m_tileWidth, m_tileHeight, TheGame::Instance()->getRenderer());
	break;

	case 1: TheTextureManager::Instance()->draw("grassTile", isoX, isoY,
			m_tileWidth, m_tileHeight, TheGame::Instance()->getRenderer());
	break;

	default: return;
	}

}

int TileHandler::getWalkCost(int tileID)
{
	switch (tileID)
	{
	case 1: return 1;
	break;

	default: return 1000;
	}
}

std::string TileHandler::getTileID(int tileID)
{
	switch (tileID)
	{
	case 0: return "grassTile";
	case 1: return "grassTile";

	default: return "";
	}
}

bool TileHandler::isWalkable(int tileID)
{
	switch (tileID)
	{
	case 0: return false;
	case 1: return true;
	default: return false;
	}
}

bool TileHandler::isNavigable(int tileID)
{
	switch (tileID)
	{
	case 0: return false;
	case 1: return false;
	default: return false;
	}
}

