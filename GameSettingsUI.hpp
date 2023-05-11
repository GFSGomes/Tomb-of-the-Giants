#pragma once
#include "UI.hpp"

struct GameSettingsUI : UI
{
	GameSettingsUI();
	~GameSettingsUI();

	bool Initialize();
};

extern GameSettingsUI UI_GameSettings;