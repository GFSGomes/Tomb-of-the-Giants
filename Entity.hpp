#pragma once
#include "GameObject.hpp"
#include "AbilityCast.hpp"
#include "Inventory.hpp"
#include "Weapon.hpp";
#include "Potion.hpp";

struct Archetype;
enum class Ability;

struct Entity : GameObject
{
	#pragma region Variables
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
	float accuracy; // short
	float dodge;
	float critical_chance;
	float critical_damage;
	float flee_rate;
	
	bool alive;
	#pragma endregion

	Inventory inventory;
	std::vector<Ability> abilities;
	std::shared_ptr<Archetype> archetype;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
	void ApplyEquipedItemStats();
	void ChangeEquipment(std::shared_ptr<Equipment>, bool);
	void ManageInventory();
	void UpdateStatus(bool, bool);
	void DisplayStatus();
};