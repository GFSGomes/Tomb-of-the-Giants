#pragma once
#include "GameObject.hpp"

struct Item : GameObject
{
	short stack;
	short dropRate;

	Item(const char*, short);
	virtual ~Item() = 0;
};