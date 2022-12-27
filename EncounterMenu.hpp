#pragma once
#include "Menu.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

struct EncounterMenu : Menu
{
	EncounterMenu();
	~EncounterMenu();

	void Battle(std::shared_ptr<Player>, std::shared_ptr<Enemy>);
	void Initialize(std::shared_ptr<Player>, std::shared_ptr<Enemy>);
};

extern EncounterMenu encounterMenu;