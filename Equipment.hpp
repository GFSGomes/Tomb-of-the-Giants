#pragma once
#include "Item.hpp"
#include "Player.hpp"

struct Equipment : Item
{
	Equipment(const char*);
	virtual ~Equipment() = 0;

	void Use();
};