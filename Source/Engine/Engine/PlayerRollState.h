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
	PlayerRollState(Player&, float = PS_ROLL_DURATION);
	~PlayerRollState();

	void initialize();
	void update(float);
	void stateEnd();

private:
	Timer<PlayerRollState>* timer;
};