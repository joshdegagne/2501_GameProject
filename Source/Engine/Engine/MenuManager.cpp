#include "MenuManager.h"
#include "Game.h"
#include "ControllerInputManager.h"
#include "KeyInput.h"
#include "ModelManager.h"
#include "MainMenu.h"
#include "PlayerSelectMenu.h"
#include "PauseMenu.h"
#include "ControlsMenu.h"
#include "CreditsMenu.h"
#include "MainMenuViewModel.h"

#include "DebugDefinitions.h"

MenuManager::~MenuManager()
{
	delete mainMenu;
	delete playerSelectMenu;
	delete pauseMenu;
	delete controlsMenu;
	delete creditsMenu;
}

bool MenuManager::initialize(Game& g)
{
	game = &g;

	mainMenu		 = new MainMenu(this);
	playerSelectMenu = new PlayerSelectMenu(this);
	pauseMenu		 = new PauseMenu(this);
	controlsMenu	 = new ControlsMenu(this);
	creditsMenu		 = new CreditsMenu(this);

	mmvm		 = new MainMenuViewModel(g);

	//game->getModelManager()->add(*mainMenu);
	//game->getModelManager()->add(*pauseMenu);
	//game->getModelManager()->add(*controlsMenu);
	//game->getModelManager()->add(*creditsMenu);

	UP_FLAG = DOWN_FLAG = CONFIRM_FLAG = CLOSE_FLAG = false;

	addMainMenu();

	return true;
}

void MenuManager::update(float elapsedTime)
{
	if (menuOrderStack.empty())
		return;

	////////////////////
	//Controller Input//
	////////////////////
	ControllerInputManager* controller = game->getControllerManager();
	if (controller->isConnected(0))
	{
		for (int i = 0; i < 1; ++i)
		{
			////////////////
			//Stick Checks//
			////////////////
			float LSY = controller->getLS_Y(i);
			if (LSY > STICK_MOVEMENT_THRESHOLD)
			{
				if (!UP_FLAG)
				{
					writeTextToConsole(L"UP!");
					UP_FLAG = true;
					menuOrderStack.top()->scrollUp();
				}
			}
			else
				UP_FLAG = false;

			if (LSY < -STICK_MOVEMENT_THRESHOLD)
			{
				if (!DOWN_FLAG)
				{
					writeTextToConsole(L"DOWN!");
					DOWN_FLAG = true;
					menuOrderStack.top()->scrollDown();
				}
			}
			else
				DOWN_FLAG = false;

			/////////////////
			//Button Checks//
			/////////////////
			if (controller->getButtonA(i))
			{
				if (!CONFIRM_FLAG)
				{
					writeTextToConsole(L"CONFIRM!");
					CONFIRM_FLAG = true;
					menuOrderStack.top()->confirmSelection();
				}
			}
			else
				CONFIRM_FLAG = false;

			if (controller->getButtonB(i))
			{
				if (!CLOSE_FLAG)
				{
					writeTextToConsole(L"CLOSE!");
					CLOSE_FLAG = true;
					if (menuOrderStack.top() != mainMenu)
						removeCurrentMenu();
				}
			}
			else
				CLOSE_FLAG = false;
		}
	}
	/////////////
	//Key Input//
	/////////////
	else
	{
		KeyInput* keyboard = game->getKeyInput();
		for (int i = 1; i < 2; ++i)
		{
			if (keyboard->IsKeyDown(keyboard->playerKeys[i][2])) //UP
			{
				if(!UP_FLAG)
				{
					writeTextToConsole(L"UP!");
					UP_FLAG = true;
					menuOrderStack.top()->scrollUp();
				}
			}
			else
				UP_FLAG = false;
			if (keyboard->IsKeyDown(keyboard->playerKeys[i][3])) //DOWN
			{
				if(!DOWN_FLAG)
				{
					writeTextToConsole(L"DOWN!");
					DOWN_FLAG = true;
					menuOrderStack.top()->scrollDown();
				}
			}
			else
				DOWN_FLAG = false;
			if (keyboard->IsKeyDown(keyboard->playerKeys[i][4])) //CONFIRM
			{
				if(!CONFIRM_FLAG)
				{
					writeTextToConsole(L"CONFIRM!");
					CONFIRM_FLAG = true;
					menuOrderStack.top()->confirmSelection();
				}
			}
			else
				CONFIRM_FLAG = false;
		}
	}
}

///////////////////////////
//Menu Control Management//
///////////////////////////
void MenuManager::removeCurrentMenu()
{
	if (menuOrderStack.empty())
		return;

	menuOrderStack.top()->setActive(false);
	menuOrderStack.top()->resetSelection();
	menuOrderStack.pop();
	if (!menuOrderStack.empty())
		menuOrderStack.top()->setActive(true);
	
	writeTextToConsole(L"CURRENT MENU REMOVED");
}
void MenuManager::removeAllMenus()
{
	while (!menuOrderStack.empty())
		removeCurrentMenu();
}
void MenuManager::addMainMenu()
{
	writeTextToConsole(L"MAIN MENU ADDED");
	addMenu(mainMenu);
}
void MenuManager::addPlayerSelectMenu()
{
	if (PLAYER_NUMBER_OVERRIDE)
	{
		sendStartGameSignal(PLAYER_NUMBER_OVERRIDE);
	}
	else
	{
		writeTextToConsole(L"PLAYER SELECT MENU ADDED");
		addMenu(playerSelectMenu);
	}
}
void MenuManager::addPauseMenu()
{
	writeTextToConsole(L"PAUSE MENU ADDED");
	addMenu(pauseMenu);
}
void MenuManager::addControlsMenu()
{
	writeTextToConsole(L"CONTROLS MENU ADDED");
	addMenu(controlsMenu);
}
void MenuManager::addCreditsMenu()
{
	writeTextToConsole(L"CREDITS MENU ADDED");
	addMenu(creditsMenu);
}
void MenuManager::addMenu(Menu* newMenu)
{
	if(!menuOrderStack.empty())
		menuOrderStack.top()->setActive(false);
	menuOrderStack.push(newMenu);
	menuOrderStack.top()->setActive(true);
}

//////////////////////////////
//Signals from Menus to Game//
//////////////////////////////
void MenuManager::sendStartGameSignal(int numPlayers)
{
	removeAllMenus();
	game->HandleStartGameSignal(numPlayers);
}
void MenuManager::sendEndGameSignal()
{
	game->HandleEndGameSignal();
}
void MenuManager::sendEndProgramSignal()
{
	game->HandleEndProgramSignal();
}
void MenuManager::sendUnPauseSignal()
{
	removeCurrentMenu();
	game->HandleUnPauseSignal();
}

void MenuManager::draw(Game& g)
{
	mmvm->Draw(mainMenu);
	//g.getGraphics()->getD3D()->getSwapChain()->Present(0,0);
}