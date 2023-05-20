#pragma once
#include "Item.hpp"

struct Consumable : Item
{
	Consumable(const char * _name = "Consumable Item", short _maxStack = 5);
	virtual ~Consumable() = 0;
};