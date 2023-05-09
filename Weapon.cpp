#include "Weapon.hpp"

Weapon::Weapon(WeaponType _weapType, const char* _name, const char* _desc, short _bonus_might, short _bonus_magic) : Equipment(_name, EquipmentClass::WEAPON)
{
	name = name;
	description = _desc;
	b_might = _bonus_might;
	b_magic = _bonus_magic;

	switch (_weapType)
	{
		case WeaponType::SWORD:
			sprite = Sprite::OH_SWORD;
			break;
		case WeaponType::AXE:
			sprite = Sprite::OH_AXE;
			break;
	}
}

Weapon::~Weapon()
{

}