#pragma once
#include "Item.hpp"
#include "Player.hpp"

struct Equipment : Item
{
	Equipment();
	virtual ~Equipment() = 0;

	void Use();
	virtual void Equip();
};