#pragma once
#include "GameObject.hpp"
#include "AbilityCast.hpp"
#include "Inventory.hpp"
#include "Weapon.hpp";
#include "Potion.hpp";
//#include <iomanip>;

struct Archetype;
enum class Ability;

struct Entity : GameObject
{
	#pragma region Variables
	short level;
	short status_points;
	
	short STR;
	short CON;
	short INT;
	short AGI;
	short DEX;

	short _bleedind_turns; float bleed_damage;
	short _poisoned_turns; float poison_damage;
	short _stunned_turns;  bool  can_fight;
	
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

	float accuracy;
	float dodge;
	float flee;

	float critical_chance;
	float critical_damage;
	
	bool alive;
	#pragma endregion

	Inventory inventory;
	std::vector<Ability> abilities;
	std::shared_ptr<Archetype> archetype;


	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
	std::string UpdateSideEffects();
	void ApplyEquipedItemStats();
	void ChangeEquipment(std::shared_ptr<Equipment>, bool);
	void DrinkPotion(std::shared_ptr<Potion>);
	void ManageInventory();
	void UpdateStatus(bool);
	void DisplayStatus();
};