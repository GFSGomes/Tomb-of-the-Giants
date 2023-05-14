#include "Weapon.hpp"
/// <summary>
/// 
/// </summary>
/// <param name="_weapType"></param>
/// <param name="_name"></param>
/// <param name="_desc"></param>
/// <param name="_physical"></param>
/// <param name="_magical"></param>
/// <param name="_accuracy"></param>
/// <param name="_critical_chance"></param>
/// <param name="_critical_damage"></param>
Weapon::Weapon(
	WeaponType _weapType, 
	const char* _name, const char* _desc,
	short _physical = 0, short _magical = 0, short _accuracy = 0,
	float _critical_chance = 0, float _critical_damage = 0 ) :
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