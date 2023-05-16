#pragma once
#include "UI.hpp"
#include <memory>
#include <vector>

struct GameObject;
struct Player;

struct GameInterfaceUI : UI
{
	GameInterfaceUI();
	~GameInterfaceUI();

	bool Initialize();
	bool Initialize(std::shared_ptr<Player>);
	void Input(std::shared_ptr<Player>, std::vector<std::shared_ptr<GameObject>>);
};

extern GameInterfaceUI UI_GameInterface;