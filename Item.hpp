#pragma once
#include "GameObject.hpp"

struct Item : GameObject
{
	short stack;

	Item(const char*, short);
	virtual ~Item() = 0;
};