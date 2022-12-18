#pragma once
#include "Menu.hpp"
#include "SceneManager.hpp"

struct MainMenu : Menu
{
	MainMenu();
	~MainMenu();

	void Initialize();
};

extern MainMenu mainMenu;