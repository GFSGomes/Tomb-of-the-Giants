#pragma once
#include "Renderer.hpp"
#include <conio.h>
#include "Enemy.hpp"
#include "Player.hpp"

struct UI
{
	bool active;
	char  input;
	short index;

	UI();
	virtual ~UI() = 0;

	virtual bool Initialize() = 0;
};