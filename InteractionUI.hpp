#pragma once
#include "UI.hpp"

struct InteractionUI : UI
{
	std::string battleLog;
	std::string battleEffect;

	InteractionUI();
	~InteractionUI();

	void StartCombat(std::shared_ptr<Player>, std::shared_ptr<Enemy>, bool);
	void InteractionEnemy(std::shared_ptr<Player>, std::shared_ptr<Enemy>);
	bool InteractionItem(std::shared_ptr<Player>, std::shared_ptr<Item>);

	bool Initialize() override;
	bool Initialize(std::shared_ptr<Player>, std::shared_ptr<GameObject>);
};

extern InteractionUI UI_Interaction;