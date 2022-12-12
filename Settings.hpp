#pragma once
#include "Menu.hpp"

struct Settings : Menu
{
	Settings();
	~Settings();

	void Initialize();
};

extern Settings settings;