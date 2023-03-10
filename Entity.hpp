#pragma once
#include "GameObject.hpp"
#include "Inventory.hpp"

struct Archetype;

struct Entity : GameObject 
{
	short level;
	short status_points;
	short CON; // Increases Maximum Health and Physical Damage
	short INT; // Increases Maximum Mana and Magical Damage
	short RES; // Increases Physical Damage Mitigation
	short WIS; // Increases Magical Damage Mitigation
	short DEX; // Increases Dodge, Critical Chance and slightly increases Flee rate;
	short turns_stunned;
	short turns_poisoned;
	
	float max_experience;
	float cur_experience;
	float max_health;
	float cur_health;
	float max_mana;
	float cur_mana;
	float physical_damage;
	float magical_damage;
	float physical_resistance;
	float magical_resistance;
	short accuracy;
	float dodge;
	float critical_chance;
	float critical_damage;
	float flee_rate;
	
	bool alive;

	Inventory inventory;
	std::shared_ptr<Archetype> archetype;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
	void UpdateStatus(bool);
	void DisplayStatus();
};