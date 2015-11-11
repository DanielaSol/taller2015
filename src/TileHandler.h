#ifndef TILEHANDLER_H_
#define TILEHANDLER_H_

#include <string>

class TileHandler
{
public:
	TileHandler();

	void loadTiles();
	void drawTile(int tileID, int isoX, int isoY);

	bool isWalkable(int tileID);
	bool isNavigable(int tileID);
	bool isGetable(int tileID);
	int getWalkCost (int tileID);
	std::string getTileID (int tileID);
	bool isInteractuable(int tileID);

private:
	int m_tileWidth;
	int m_tileHeight;
};

#endif /* TILEHANDLER_H_ */
