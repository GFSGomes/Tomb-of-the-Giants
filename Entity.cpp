#pragma once
#include "Entity.hpp"

Entity::Entity() : level{0}, freeStatPoints{0}, max_experience{0}, cur_experience{0},
CON{0}, INT{0}, RES{0}, WIS{0}, DEX{0},
max_health{0}, cur_health{0}, physical_damage{0}, physical_resistance{0},
max_mana{0}, cur_mana{0}, magical_damage{0}, magical_resistance{0},
dodge_rate{0}, critical_rate{0}, flee_rate{0},
state_stun{0}, state_confusion{0}, state_poison{0},
alive{true}
{

}

Entity::~Entity()
{

}

void Entity::Actions()
{

}

void Entity::DisplayStatus()
{
	std::cout << name << " (" << level << ")\n";
	std::cout << "Exp : " << cur_experience << "/" << max_experience << "\n";

	std::cout << "HP ";
	for (short i = 0; i < cur_health; i++) std::cout << "=";
	for (short i = 0; i < cur_health - max_health; i++) std::cout << "-";
	std::cout << "\n";

	std::cout << "MP ";
	for (short i = 0; i < cur_mana; i++) std::cout << "=";
	for (short i = 0; i < cur_mana - max_mana; i++) std::cout << "-";
	std::cout << "\n";

	std::cout << " CON | " << CON << "   Physical Damage | " << physical_damage << "\n";
	std::cout << " INT | " << INT << "   Magical Damage  | " << magical_damage  << "\n";
	std::cout << " RES | " << RES << "   Physical Resistance | " << physical_damage << "\n";
	std::cout << " WIS | " << WIS << "   Magical Resistance  | " << magical_resistance << "\n";
	std::cout << " DEX | " << DEX << "   Dodge | " << dodge_rate << "   Critical Chance | " << critical_rate << "   Flee | " << flee_rate << "\n";
}

void Entity::UpdateStatus(bool _levelUp)	
{											// LEVEL 10				// LEVEL 25
	max_health = 15 + CON * 1.5;			// 30.0	HP				52.5 HP
	max_mana   = 10 + INT;					// 20.0	MP				45.0 MP

	physical_damage = 1 + (CON * 0.15);		// 2.5 PD				4.75 PD
	magical_damage  = 1 + (INT * 0.20);		// 3.5 MD				6.00 MD

	physical_resistance = RES * 0.15;		// 1.5 PR				3.75 PR
	magical_resistance  = WIS * 0.20;		// 2.0 MR				5.00 MR

	dodge_rate		= 5 + DEX * 0.08;		// 5.25 Dodge			7.00 Dodge
	critical_rate	= 1 + DEX * 0.05;		// 1.50 Crit			2.25 Crit
	flee_rate		= 5 + DEX * 0.50;		// 10.0 Flee			17.5 Flee

	cur_health > 0 ? alive = true : alive = false;

	if (_levelUp)
	{
		level++;
		cur_experience = 0;
		max_experience *= 0.15;

		cur_health	= max_health;
		cur_mana	= max_mana;

		UpdateStatus(false);
	}
}