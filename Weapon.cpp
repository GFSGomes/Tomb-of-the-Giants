#include "Weapon.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"

Weapon::Weapon(
	WeaponType _weapType, 
	const char* _name, const char* _desc,
	float _physical, float _magical, short _accuracy,
	float _critical_chance, float _critical_damage) 
	:
	weaponType{_weapType},
	physical_power{_physical},
	magical_power{_magical},
	accuracy{_accuracy},
	critical_chance{_critical_chance},
	critical_damage{_critical_damage},
	Equipment(_name, EquipmentClass::WEAPON)
{
	description = _desc;

	switch (weaponType)
	{
		case WeaponType::SWORD:
			sprite = Sprite::OH_SWORD;
			break;
		case WeaponType::AXE:
			sprite = Sprite::OH_AXE;
			break;
		case WeaponType::DAGGER:
			sprite = Sprite::DAGGER;
			break;
	}
}

Weapon::~Weapon()
{

}