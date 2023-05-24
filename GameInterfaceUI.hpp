#pragma once
#include "UI.hpp"
#include <memory>
#include <vector>

struct GameObject;
struct Player;
struct Enemy;
struct Scene;

struct GameInterfaceUI : UI
{
	bool _resources_manip;
	bool _exp_manip;
	bool _level_manip;
	bool _torch_manip;

	GameInterfaceUI();
	~GameInterfaceUI();

	bool Initialize();
	bool Initialize(std::shared_ptr<Player>);
	char Input(std::shared_ptr<Player> player, std::vector<std::shared_ptr<GameObject>> &SceneOBJs, short _inputDelay = 20);
};

extern GameInterfaceUI UI_GameInterface;