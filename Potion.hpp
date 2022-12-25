#pragma once
#include "Item.hpp"

struct Potion : Item
{
	Potion(const char*);
	~Potion();

	void Use();
};