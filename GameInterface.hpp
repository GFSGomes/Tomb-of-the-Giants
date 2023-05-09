#pragma once
#include "GUI.hpp"
#include "Player.hpp"


struct GameInterface : GUI
{
	GameInterface();
	~GameInterface();

	void Initialize();
	void Initialize(std::shared_ptr<Player>);
	void Input(std::shared_ptr<Player>);
};

extern GameInterface GUI_Controls;