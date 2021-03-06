///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "Obstacle.h"
#include "ObstacleBag.h"
#include "Game.h"
#include "LogObstacle.h"
#include "RockObstacle.h"
#include "EntityType.h"
#include "CollisionManager.h"

#define SCROLL_SPEED 0.15f
#define NUM_LANES 6

class Player; //Foward declaration needed in order to satisfy compiler
class Game;
////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield : public ITimedObject
{
	public:
		Playfield(); //Game pointer can come out of here when we no longer have test players
		~Playfield();

		void initialize(Game*, int);
		void update(float); // for scrolling

		void timerCallback(Timer&);

		float getLength()	{ return fieldLength; }
		float getWidth()	{ return fieldWidth; }

		float getScrollAmount() { return scrollAmount; }

		EntityType getEntityType() { return EntityType::PLAYFIELD; }

	private:
		Game* game;
		ArrayList<Entity>*		entities;			//List of entities CURRENTLY BEING UPDATED
		ArrayList<Player>*		activePlayers;		//List of players in the current match
		ObstacleBag*			obstacleBag;

		CollisionManager*		collisionManager;
		AudioManager*           audioManager;

		float scrollAmount;

		Timer playTimer;
		float previousProgressPercentage;
		float percentageBetweenObstacles;

		bool  endFlag;
		Timer endTimer;

		const float fieldLength;
		const float fieldWidth;

		void populateLists(Game*, int);

		int getLaneAlgorithm(Obstacle*);
		void addObstacleToPlayfield();
		void kill(Entity*);
		void placeObstacle(Obstacle*, int lane = -1);

		void checkPlayerBounds(Player*);

};