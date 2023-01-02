#pragma once
#include "Renderer.hpp"
#include <conio.h>

extern bool DebugMode;

struct GUI
{
	bool active;
	short index;
	char input;

	GUI();
	virtual ~GUI() = 0;

	virtual void Initialize() = 0;
};