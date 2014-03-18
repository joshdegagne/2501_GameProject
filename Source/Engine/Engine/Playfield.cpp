#include "Playfield.h"
#include <random>
#include "DebugDefinitions.h"

////////////////////////
#include "PlayerViewModel.h"
#include "LogViewModel.h"
#include "RockViewModel.h"
#include "ViewModel.cpp"
#include "ModelManager.h"
#include "ModelManager-inl.h"
////////////////////////



Playfield::Playfield() : fieldLength(30.0f), fieldWidth(6.0f), previousProgressPercentage(0.0f), percentageBetweenObstacles(1/(GAME_LENGTH/1000.0f)), endFlag(false)
{
	entities = new ArrayList<Entity>;
	activePlayers = new ArrayList<Player>;
	obstacleBag = new ObstacleBag;
}

Playfield::~Playfield()
{
	game->getModelManager()->cleanUpArrayMemory();
	collisionManager->cleanUpArrayMemory();
	delete entities;
	delete activePlayers;
	delete obstacleBag;

	entities = 0;
	activePlayers = 0;
	obstacleBag = 0;
}

void Playfield::initialize(Game* g)
{
	game = g;
	collisionManager = game->getCollisionManager();

	playTimer.initialize(GAME_LENGTH, this);
	endTimer.initialize(END_LENGTH, this);

	populateLists(game);

	for(int i = 0; i < activePlayers->size(); ++i)
	{
		game->getModelManager()->add(*activePlayers->elementAt(i));
		collisionManager->addPlayerReference(*activePlayers->elementAt(i));
		#ifdef COLLISION_DEBUG
		game->getModelManager()->add(*activePlayers->elementAt(i)->getBound());
		#endif
	}
	for(int i = 0; i < obstacleBag->getNumObstacles(); ++i)
	{
		game->getModelManager()->add(*obstacleBag->getObstacle(i));
		collisionManager->addObstacleReference(*obstacleBag->getObstacle(i));
		#ifdef COLLISION_DEBUG
		game->getModelManager()->add(*obstacleBag->getObstacle(i)->getBound());
		#endif
	}
}


void Playfield::update(float elapsed) 
{
	if (!endFlag)
	{
		for (int i = 0; i < activePlayers->size(); ++i)
		{
			if (activePlayers->elementAt(i)->requestingPause() && !activePlayers->elementAt(i)->isDead())
			{
				game->HandlePauseRequest(i);
				return;
			}
		}
		//Obstacle placement based on time
		///////////////////////////////////
		playTimer.update(elapsed);

		#ifndef OBSTACLE_SPAWN_DEBUG
		if (playTimer.getProgressPercentage() - previousProgressPercentage > percentageBetweenObstacles && playTimer.getProgressPercentage() < 1.0f-(2.0f*percentageBetweenObstacles) )
		{
			previousProgressPercentage = playTimer.getProgressPercentage();
			addObstacleToPlayfield();
		}
		#endif
		///////////////////////////////////

		//This for loop is backwards because for SOME REASON, putting it the other way doesn't work with tie-breakers.
		for (int i = entities->size()-1; i >=0 ; --i) 
		{
			Entity* currEntity = entities->elementAt(i);

			if (currEntity->getEntityType() == EntityType::PLAYER)
			{
				checkPlayerBounds((Player*)currEntity);
				currEntity->update(elapsed);
			}
			else
			{
				currEntity->update(elapsed);
				if (currEntity->getX() < -2.0f)
					kill(currEntity);
			}
			currEntity->getBound()->update();
		}
		collisionManager->checkForCollisions(elapsed);

		int counter = 0;
		for (int i = 0; i < activePlayers->size(); ++i)
			if (activePlayers->elementAt(i)->isDead())
				++counter;
		if (counter >= 3)
			playTimer.forceTimerEnd();
	}
	else
	{
		for (int i = 0; i < activePlayers->size(); ++i)
		{
			if (!activePlayers->elementAt(i)->isDead())
				activePlayers->elementAt(i)->moveBy(XMFLOAT2(MOVEMENT_SPEED*elapsed, 0.0f));
		}

		for (int i = 0; i < obstacleBag->getNumObstacles(); ++i)
		{
			Obstacle* currObst = obstacleBag->getObstacle(i);
			if (!currObst->isDead())
				currObst->update(elapsed);
			if (currObst->getX() < -2.0f)
				kill(currObst);
		}
		
		endTimer.update(elapsed);
	}
}

void Playfield::timerCallback(Timer& t)
{
	if (t == playTimer)
	{
		endFlag = true;
		for (int i = 0; i < activePlayers->size(); ++i)
			activePlayers->elementAt(i)->lockForwardMovement(false);
	}
	else if (t == endTimer)
		game->HandlePlayfieldEnd();
}

//////////////////////
//Intialization Code//
//////////////////////

//Creates obstacles and places them in the obstacles arraylist
void Playfield::populateLists(Game* game)
{
	for(int i = 0; i < game->GetPlayers()->size(); ++i)
	{
			Player* player = game->GetPlayers()->elementAt(i);
			activePlayers->add(player);
			entities->add(player);
	}
	obstacleBag->initialize(game);
}

/////////////////
//Obstacle Code//
/////////////////
int Playfield::getLaneAlgorithm(Obstacle* obstacle)
	{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_LANES-1);
	
	while(1)
	{
		int selectedLane = dis(gen);
		if (selectedLane <= NUM_LANES - obstacle->getLength())
			return selectedLane;
	}
}



void Playfield::addObstacleToPlayfield()
{
	Obstacle* selectedObstacle = obstacleBag->pullRandomObstacle();
	if (selectedObstacle == nullptr)
		return;
	int selectedLane = getLaneAlgorithm(selectedObstacle);
	placeObstacle(selectedObstacle, selectedLane);
}

void Playfield::kill(Entity* entity)
{
	entities->remove(entity);
	entity->moveTo(DEAD_X, DEAD_Y); //Moves off to the side (should only be visible for testing)
	entity->setDead(true);
}


//Places input obstacle at the "beginning" of the playfield. Optional: Specific lane input
void Playfield::placeObstacle(Obstacle* obstacle, int lane)
{
	if (lane == -1)
		lane = 0;
	else if (lane >= NUM_LANES)
		lane = NUM_LANES - 1;

	float laneLength = fieldWidth/NUM_LANES;
	obstacle->moveTo(fieldLength, (laneLength)*(lane));
	entities->add(obstacle);
	obstacle->setDead(false);
}

///////////////
//Player Code//
///////////////
void Playfield::checkPlayerBounds(Player* player)
{
	XMFLOAT3 position = player->getPosition(); 

	if (position.y + player->getBound()->getDimensions()->y >= fieldWidth)
	{
		player->lockLeftMovement();
	}
	else if (position.y - player->getBound()->getDimensions()->y <= 0)
	{
		player->lockRightMovement();
	}
	if (position.x + player->getBound()->getDimensions()->x >= (fieldLength - 3.0f))
	{
		player->lockForwardMovement();
	}
	else if (position.x - player->getBound()->getDimensions()->x <= 0)
	{
		kill(player);
	}
	
	
}