////////////////////////////////////////////////////////////////////////////////
// Filename: MenuManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "IManager.h"
#include "Menu.h"
#include <stack>

class MainMenu;
class PauseMenu;
class ControlsMenu;
class CreditsMenu;
class MainMenuViewModel;

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
	void sendUnPauseSignal();

	//std::stack<Menu*> getMenuOrderStack();
	void draw(Game&);

private:
	Game* game;

	std::stack<Menu*>	menuOrderStack;
	MainMenu*			mainMenu;
	PauseMenu*			pauseMenu;
	ControlsMenu*		controlsMenu;
	CreditsMenu*		creditsMenu;

	MainMenuViewModel*	mmvm;

	bool UP_FLAG, DOWN_FLAG, CONFIRM_FLAG, CLOSE_FLAG;

	void addMenu(Menu*);
};