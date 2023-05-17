#pragma once
#include "Equipment.hpp"

enum class WeaponType
{
	AXE, SWORD, DAGGER, STAFF, BOW
};

struct Weapon : Equipment
{
	WeaponType weaponType;
	
	float physical_power;
	float magical_power;
	short accuracy;
	float critical_chance;
	float critical_damage;

	Weapon(WeaponType, const char*, const char*, float, float, short, float, float);
	~Weapon();
};