#pragma once
#include "GUI.hpp"

struct Settings : GUI
{
	Settings();
	~Settings();

	void Initialize() override;
};

extern Settings settings;