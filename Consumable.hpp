#pragma once
#include "Item.hpp"
#include <memory>

struct Entity;

struct Consumable : Item
{
	Consumable(const char * _name = "Consumable Item", short _maxStack = 5);
	virtual ~Consumable() = 0;

	virtual float Use(std::shared_ptr<Entity>);
};