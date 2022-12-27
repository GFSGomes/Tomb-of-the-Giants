#include "Weapon.hpp"

Weapon::Weapon(WeaponType _weapType, const char* _name, const char* _desc, short _bonus_might, short _bonus_magic) : Equipment(_name)
{
	name = name;
	description = _desc;
	b_might = _bonus_might;
	b_magic = _bonus_magic;
}

Weapon::~Weapon()
{

}