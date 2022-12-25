#pragma once
#include "GameObject.hpp"
#include "Inventory.hpp"

struct Entity : GameObject 
{
	short level;
	short freeStatPoints;
	float max_experience;
	float cur_experience;

	short CON; // Increases Maximum Health and Physical Damage
	short INT; // Increases Maximum Mana and Magical Damage
	short RES; // Increases Physical Damage Mitigation
	short WIS; // Increases Magical Damage Mitigation
	short DEX; // Increases Dodge, Critical Chance and slightly increases Flee rate;

	float max_health;
	float cur_health;
	float physical_damage;
	float physical_resistance;

	float max_mana;
	float cur_mana;
	float magical_damage;
	float magical_resistance;

	float dodge_rate;
	float critical_rate;
	float flee_rate;

	short state_stun;
	short state_poison;
	short state_confusion;
	
	bool alive;

	Inventory inventory;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
	void UpdateStatus(bool);
	void DisplayStatus();
};