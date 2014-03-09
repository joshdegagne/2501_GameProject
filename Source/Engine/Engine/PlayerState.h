////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "arraylist.h"
#include "Timer.h"

// Forward Declarations
class Player;
class Obstacle;

////////////////////////////////////////////////////////////////////////////////
// Abstract class name: PlayerState
////////////////////////////////////////////////////////////////////////////////
class PlayerState {
public:
	PlayerState(Player&, float);

//	virtual void onCollideWith(Player*)   = 0;
//	virtual void onCollideWith(Obstacle*) = 0;
	virtual void initialize()  = 0;
	virtual void update(float) = 0;
	virtual void stateEnd()    = 0;

protected:
	Player& player;
	float   stateDuration;
};