////////////////////////////////////////////////////////////////////////////////
// Filename: IPlayerListener.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

class PlayerState;

///////////////////////////////////////////////////////////////////////////////
// Interface Name: IPlayerListener
////////////////////////////////////////////////////////////////////////////////
class IPlayerListener {
public:
	virtual void onStateStart(PlayerState&)  = 0;
	virtual void onStateEnd(PlayerState&)    = 0;
};