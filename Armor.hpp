#pragma once
#include "Equipment.hpp"

enum class ArmorType
{
	BODY, HEAD, ARMS, LEGS
};

struct Armor : Equipment
{
	ArmorType _type;

	short bonus_physical_resistance;
	short bonus_magical_resistance;

	short bonus_CON;
	short bonus_AGI;
	short bonus_INT;

	Armor();
	~Armor();
};