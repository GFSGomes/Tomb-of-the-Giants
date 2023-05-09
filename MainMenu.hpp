#pragma once
#include "GUI.hpp"
#include "SceneManager.hpp"

struct MainMenu : GUI
{
	Renderer renderer;

	MainMenu();
	~MainMenu();

	void Initialize();
};

extern MainMenu mainMenu;