////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerInjuredState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "PlayerState.h"

////////////////////////////////////////////////////////////////////////////////
// Class Name: PlayerInjuredState
////////////////////////////////////////////////////////////////////////////////
class PlayerInjuredState : public PlayerState {
public:
	PlayerInjuredState(Player&, float);
	~PlayerInjuredState();

	void initialize();
	void update();
	void stateEnd();

private:
	Timer<PlayerInjuredState>* timer;
};