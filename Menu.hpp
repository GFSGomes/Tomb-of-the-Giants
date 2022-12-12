#pragma once
#include "Renderer.hpp"
#include <conio.h>

extern bool DebugMode;

struct Menu
{
	bool active;
	short index;
	char input;

	Menu();
	virtual ~Menu() = 0;

	virtual void Initialize();
};