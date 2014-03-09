#include "PlayerRegularState.h"
#include "Timer-inl.h"

PlayerRegularState::PlayerRegularState(Player& p, float duration = -1.0f) : PlayerState(p, duration)
{
	timer = new Timer<PlayerRegularState>;
	initialize();
}

PlayerRegularState::~PlayerRegularState()
{
	
}

void PlayerRegularState::initialize()
{
	timer->initialize(0.0f, &PlayerRegularState::stateEnd);
}

void PlayerRegularState::update()
{
	
}

void PlayerRegularState::stateEnd()
{
	
}
