/*
 * MapSearchNode.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: gonzalo
 */

#include "MapSearchNode.h"
#include "stlastar.h"
#include "../Game.h"
#include <math.h>

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{
	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.
float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	MapSearchNode NewNode;
	bool validNode = true;
	int tileValue;
	// push each possible move except allowing the search to go backwards

	//MOVIMIENTOS RECTOS (en relacion a las coordenadas)
	validNode = ((x - 1) >= 0);
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x-1][y];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x-1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = ((y - 1) >= 0);
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x][y-1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x) && (parent_y == y-1))
	  )
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = ((x + 1) <= TheGame::Instance()->getMapWidth());
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x+1][y];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x+1) && (parent_y == y))
	  )
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = ((y + 1) <= TheGame::Instance()->getMapHeight());
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x][y+1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	// MOVIMIENTOS DIAGONALES
	validNode = (((y + 1) <= TheGame::Instance()->getMapHeight()) && (((x + 1) <= TheGame::Instance()->getMapWidth())));
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x+1][y+1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x+1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x+1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = (((y - 1) >= 0) && (((x - 1) >= 0)));
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x-1][y-1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x-1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x-1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = (((y - 1) >= 0) && (((x + 1) <= TheGame::Instance()->getMapWidth())));
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x+1][y-1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x+1) && (parent_y == y-1))
		)
	{
		NewNode = MapSearchNode( x+1, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}

	validNode = (((y + 1) <= TheGame::Instance()->getMapHeight()) && (((x - 1) >= 0)));
	if (validNode)
		tileValue = TheGame::Instance()->m_pMap->m_mapGrid[x-1][y+1];
	if( validNode && (TheGame::Instance()->m_pMap->m_pTileHandler->isWalkable(tileValue))
		&& !((parent_x == x-1) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x-1, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}

	return true;
}
float toIsometricX(int x, int y)
{
	return (x - y);
}
float toIsometricY(int x, int y)
{
	return ((x + y) / 2);
}

float MapSearchNode::GetCost( MapSearchNode &successor )
{

	int cost = TheGame::Instance()->m_pMap->m_pTileHandler->getWalkCost(TheGame::Instance()->m_pMap->m_mapGrid[successor.x][successor.y]);
	return (float) cost;
}



