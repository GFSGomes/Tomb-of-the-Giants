#pragma once
#include "Equipment.hpp"
#include "Ability.hpp"

struct Weapon : Equipment
{
	Ability ability[4];

	Weapon();
	~Weapon();
};