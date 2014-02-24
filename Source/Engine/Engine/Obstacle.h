///////////////////////////////////////////////////////////////////////////////
// Filename: Obstacle.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "Entity.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Obstacle
////////////////////////////////////////////////////////////////////////////////
class Obstacle : public Entity
{
	public:
		Obstacle(float); // initialized to not be present on the playfield (present = false)
		Obstacle(float, bool);
		float getLength();
		bool isPresent();
		void setPresent(bool);
	protected:
		//Type of obstacle
		//Obstacle size?
		float length;
		bool present; // whether the obstacle is on screen and moving towards players

};