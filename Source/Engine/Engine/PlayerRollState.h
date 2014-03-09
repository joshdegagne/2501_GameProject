////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerRollState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "PlayerState.h"

////////////////////////////////////////////////////////////////////////////////
// Class Name: PlayerRollState
////////////////////////////////////////////////////////////////////////////////
class PlayerRollState : public PlayerState {
public:
	PlayerRollState(Player&, float);
	~PlayerRollState();

	void initialize();
	void update();
	void stateEnd();

private:
	Timer<PlayerRollState>* timer;
};