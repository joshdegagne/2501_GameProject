///////////////////////////////////////////////////////////////////////////////
// Filename: ResultsMenu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Menu.h"

class MenuManager;

class ResultsMenu : public Menu
{
public:
	ResultsMenu(MenuManager* menuManager, bool active = false);
	void confirmSelection();
};