/*
 * MapSearchNode.h
 *
 *  Created on: Oct 16, 2015
 *      Author: gonzalo
 */

#ifndef SRC_ASTAR_MAPSEARCHNODE_H_
#define SRC_ASTAR_MAPSEARCHNODE_H_

#include "stlastar.h"

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x = px; y = py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );


};

#endif /* SRC_ASTAR_MAPSEARCHNODE_H_ */
