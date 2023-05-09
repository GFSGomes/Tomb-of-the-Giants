#pragma once
#include "Equipment.hpp";
#include "Entity.hpp";

enum class WeaponType
{
	AXE, SWORD, DAGGER, STAFF, BOW
};

struct Weapon : Equipment
{
	WeaponType weaponType;
	short b_might;
	short b_magic;

	Weapon(WeaponType, const char*, const char*, short, short);
	~Weapon();
};