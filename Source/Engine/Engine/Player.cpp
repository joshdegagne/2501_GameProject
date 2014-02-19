#include "Player.h"

Player::Player(Game& g, int pNum) : Entity(), playerNum(pNum)
{
	controller = g.getControllerManager();
	position.x = 0;
	position.y = 0;
	
	playerModel = new CubeModel(1.0f, 1.0f, 1.0f);
}

GameModel* Player::getPlayerModel()
{
	return playerModel;
}

void Player::render()
{
}

void Player::update(float elapsed)
{
	//Needed: 
	//  - implementation/usage of "elapsed"
	//  - Prioritization of actions?
	//	- Check for buttons being released?

	////////////////
	//Stick Checks//
	////////////////
	float LSX = controller->getLS_X(playerNum);
	if (LSX > STICK_MOVEMENT_THRESHOLD)
	{
		//moveRight();
	}
	else if (LSX < -STICK_MOVEMENT_THRESHOLD)
	{
		//moveLeft();
	}

	float LSY = controller->getLS_Y(playerNum);
	if (LSY > STICK_MOVEMENT_THRESHOLD)
	{
		//moveUp();
	}
	else if (LSY < -STICK_MOVEMENT_THRESHOLD)
	{
		//moveDown();
	}

	/////////////////
	//Button Checks//
	/////////////////
	if (controller->getButtonA(playerNum))
	{
		//Jump?
		return;
	}
	if (controller->getButtonB(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonX(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonY(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonLB(playerNum))
	{
		//Roll left? Or would that be LT?
		return;
	}
	if (controller->getButtonRB(playerNum))
	{
		//Roll right? Or would that be RT?
		return;
	}
	if (controller->getButtonStart(playerNum))
	{
		//Pause game?
		return;
	}
	if (controller->getButtonBack(playerNum))
	{
		//????
		return;
	}

	//////////////////
	//Trigger Checks//
	//////////////////
	float LT = controller->getLT(playerNum);
	if (LT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		//Roll left?
		return;
	}

	float RT = controller->getRT(playerNum);
	if (RT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		//Roll right?
		return;
	}

}

void Player::moveLeft()
{
	position.x -= MOVEMENT_SPEED;
	playerModel->worldTranslate(0.0f, +MOVEMENT_SPEED, 0.0f); //Left is "up" in our game world
}
void Player::moveRight()
{
	position.x += MOVEMENT_SPEED;
	playerModel->worldTranslate(0.0f, -MOVEMENT_SPEED, 0.0f); //Right is "down" in our game world
}
void Player::moveDown()
{
	position.y -= MOVEMENT_SPEED;
	playerModel->worldTranslate(+MOVEMENT_SPEED, 0.0f, 0.0f); //Down is "right" in our game world
}
void Player::moveUp()
{
	position.y += MOVEMENT_SPEED;
	playerModel->worldTranslate(-MOVEMENT_SPEED, 0.0f, 0.0f); //Up is "left" in our game world
}