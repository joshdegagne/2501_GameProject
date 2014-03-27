///////////////////////////////////////////////////////////////////////////////
// Filename: TreeObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TreeObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

TreeObstacle::TreeObstacle(Game& g) : Obstacle(g, 1.0f, 5.0f)
{
	type = EntityType::TREE;

	bound->initialize(this);
}