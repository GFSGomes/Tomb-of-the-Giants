#pragma once
#include "Item.hpp"

struct Equipment : Item
{
	Equipment(const char*);
	virtual ~Equipment() = 0;
};