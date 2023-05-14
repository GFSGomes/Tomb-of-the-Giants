#pragma once
#include "Equipment.hpp"
#include "Entity.hpp"

enum class WeaponType
{
	AXE, SWORD, DAGGER, STAFF, BOW
};

struct Weapon : Equipment
{
	WeaponType weaponType;
	
	short physical_power;
	short magical_power;
	short accuracy;
	float critical_chance;
	float critical_damage;

	Weapon(WeaponType, const char*, const char*, short, short, short, float, float);
	~Weapon();
};