#pragma once
#include "Item.hpp"

struct Slot
{
	std::shared_ptr<Item> item;
	short amount;

	Slot(std::shared_ptr<Item>, short);

	~Slot();
};