#pragma once
#include "GUI.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

struct InteractionInterface : GUI
{
	InteractionInterface();
	~InteractionInterface();

	void StartCombat(std::shared_ptr<Player>, std::shared_ptr<Enemy>);
	void Initialize() override;
	void Initialize(std::shared_ptr<Player>, std::shared_ptr<GameObject>);
};

extern InteractionInterface GUI_Interaction;