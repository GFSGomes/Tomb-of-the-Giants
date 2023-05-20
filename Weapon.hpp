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

	Weapon(WeaponType, const char*, const char*, float, float _bonus_magical = 0, short _accuracy = 0, float _critical_change = 0, float _critical_damage = 0);
	~Weapon();
};