#pragma once
#include "Weapon.hpp"
#include "Attack.hpp"
#include "DoubleStrike.hpp"

struct Sword : Weapon
{
	Attack attack;
	DoubleStrike doubleStrike;

	Sword();
	~Sword();
};