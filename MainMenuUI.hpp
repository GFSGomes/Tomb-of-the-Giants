#pragma once
#include "UI.hpp"
#include "SceneManager.hpp"

struct MainMenuUI : UI
{
	Renderer renderer;

	MainMenuUI();
	~MainMenuUI();

	bool Initialize();
};

extern MainMenuUI mainMenu;