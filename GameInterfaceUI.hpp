#pragma once
#include "UI.hpp"
#include "Player.hpp"

struct GameInterfaceUI : UI
{
	GameInterfaceUI();
	~GameInterfaceUI();

	bool Initialize();
	bool Initialize(std::shared_ptr<Player>);
	void Input(std::shared_ptr<Player>);
};

extern GameInterfaceUI UI_GameInterface;