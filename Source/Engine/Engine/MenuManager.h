////////////////////////////////////////////////////////////////////////////////
// Filename: MenuManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "IManager.h"
#include "Menu.h"
#include <stack>

///////////////////////////////////////////////////////////////////////////////
// Class Name: MenuManager
////////////////////////////////////////////////////////////////////////////////
class MenuManager : public IManager
{
public:
	bool initialize(Game&);
	void update(float);

	void removeCurrentMenu();
	void addMainMenu();
	void addPauseMenu();
	void addControlsMenu();
	void addCreditsMenu();

	void sendStartGameSignal();
	void sendEndGameSignal();
	void sendEndProgramSignal();

private:
	Game* game;
	std::stack<Menu*> menuOrderStack;
	//List of menus go here
	//MainMenu* mainMenu;
	//PauseMenu* pauseMenu;
	//ControlsMenu* controlsMenu;
	//CreditsMenu* creditsMenu;

	bool UP_FLAG, DOWN_FLAG, CONFIRM_FLAG, CLOSE_FLAG;
};