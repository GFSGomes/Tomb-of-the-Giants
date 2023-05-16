#pragma once
#include "UI.hpp"

struct MainMenuUI : UI
{
	MainMenuUI();
	~MainMenuUI();

	bool Initialize();
};

extern MainMenuUI mainMenu;