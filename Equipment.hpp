#pragma once
#include "Item.hpp"

enum class EquipmentClass
{
	WEAPON, ARMOR,
};

struct Equipment : Item
{
	bool equiped;
	EquipmentClass equipmentClass;

	Equipment(const char*, EquipmentClass);
	virtual ~Equipment() = 0;
};