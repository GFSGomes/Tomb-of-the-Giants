#pragma once
#include "UI.hpp"
#include <memory>
#include <iostream>
#include <vector>

struct GameObject;
struct Player;
struct Enemy;
struct Item;

struct InteractionUI : UI
{
	std::string battleLog;
	std::string battleEffect;

	InteractionUI();
	~InteractionUI();

	void StartCombat(std::shared_ptr<Player>, std::shared_ptr<Enemy>, bool);
	void InteractionEnemy(std::shared_ptr<Player>, std::shared_ptr<Enemy>, std::vector<std::shared_ptr<GameObject>>);
	bool InteractionItem(std::shared_ptr<Player>, std::shared_ptr<Item>);

	bool Initialize() override;
	bool Initialize(std::shared_ptr<Player> player, std::shared_ptr<GameObject> interactiobObject, std::vector<std::shared_ptr<GameObject>> SceneOBJs);
};

extern InteractionUI UI_Interaction;