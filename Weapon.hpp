#pragma once
#include "Equipment.hpp"

enum class WeaponType
{
	OH_AXE, TH_AXE, OH_SWORD, TH_SWORD, DAGGER, STAFF, BOW
};

struct Weapon : Equipment
{
	WeaponType weaponType;
	float physical_power;
	float magical_power;
	short accuracy;
	float critical_chance;
	float critical_damage;

	Weapon(WeaponType weaponType, const char* name, const char* description, float bonus_physical, float bonus_magical = 0, short accuracy = 0, float critical_change = 0, float critical_damage = 0);
};