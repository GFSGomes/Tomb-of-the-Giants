#pragma once
#include "Item.hpp"

struct Miscellaneous : Item
{
	Miscellaneous(const char * _name = "Miscellaneous Item", short _stack = 1);
	~Miscellaneous() = 0;
};