///////////////////////////////////////////////////////////////////////////////
// Filename: MainMenu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Menu.h"

class MenuManager;

class MainMenu : public Menu
{
public:
	MainMenu(MenuManager* menuManager, bool active = false);
	void confirmSelection();
};