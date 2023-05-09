#pragma once
#include "Renderer.hpp"
#include <conio.h>

//Reativar se der problema:
extern bool DebugMode;

struct GUI
{
	bool active;
	short index;
	char input;

	GUI();
	virtual ~GUI() = 0;

	void Initialize();
};