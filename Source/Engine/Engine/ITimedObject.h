////////////////////////////////////////////////////////////////////////////////
// Filename: ITimedObject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Interface Name: ITimedObject
////////////////////////////////////////////////////////////////////////////////
class ITimedObject {
public:
	virtual void timerCallback()  = 0;
};