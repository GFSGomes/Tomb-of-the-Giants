#pragma once
#include "Equipment.hpp"

enum class WeaponType
{
	SWORD, AXE, STAFF, BOW
};

struct Weapon : Equipment
{
	WeaponType weaponType;
	short b_might;
	short b_magic;

	Weapon(WeaponType, const char*, const char*, short, short);
	~Weapon();
};