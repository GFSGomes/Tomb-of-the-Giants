#pragma once
#include "Menu.hpp"
#include "SceneManager.hpp"

struct MainMenu : Menu
{
	Renderer renderer;

	MainMenu();
	~MainMenu();

	void Initialize();
};