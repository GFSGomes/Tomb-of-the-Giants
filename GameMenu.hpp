#pragma once
#include "Menu.hpp"
#include "Player.hpp"


struct GameMenu : Menu
{
	GameMenu();
	~GameMenu();

	void Initialize();
	void Input(std::shared_ptr<Player>);
};

extern GameMenu gameMenu;