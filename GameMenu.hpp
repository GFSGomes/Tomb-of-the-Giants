#pragma once
#include "Menu.hpp"
#include "Player.hpp"


struct GameMenu : Menu
{
	GameMenu();
	~GameMenu();

	void Initialize(std::shared_ptr<Player>);
	void Input(std::shared_ptr<Player>);
};

extern GameMenu gameMenu;