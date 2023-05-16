#pragma once
#include <memory>

struct Item;

struct Slot
{
	std::shared_ptr<Item> item;
	short amount;

	Slot(std::shared_ptr<Item>, short);
	~Slot();
};