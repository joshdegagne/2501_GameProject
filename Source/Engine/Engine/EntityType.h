////////////////////////////////////////////////////////////////////////////////
// Filename: EntityType.h
////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////
// Class name: EntityType
////////////////////////////////////////////////////////////////////////////////
enum class EntityType : int
{
	//Players
	PLAYER,
	//Obstacles
	FINISH,
	ROCK_SMALL, 
	ROCK_BIG,
	ICE_PATCH,
	ICE_SPIKE,
	SNOW_MOUND,
	SNOW_BALL,
	//Variable length obstacles.
	LOG,
	LOG_FALLING
	
};