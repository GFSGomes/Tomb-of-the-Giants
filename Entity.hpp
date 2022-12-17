#pragma once
#include "GameObject.hpp"

struct Entity : GameObject {

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
	float physical_damage;
	float max_mana;
	float magical_damage;

	float physical_resistance;
	float magical_resistance;

	float dodge_rate;
	float critical_rate;
	float flee_rate;

	float cur_health;
	float cur_mana;

	short state_stun;
	short state_poison;
	short state_confusion;
	
	bool alive;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
	void UpdateStatus(bool);
};