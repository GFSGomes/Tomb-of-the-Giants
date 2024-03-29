#pragma once
#include "GameObject.hpp"
#include "Inventory.hpp"// !Importante
#include "Potion.hpp"   // !Importante
#include <vector>
#include <memory>

struct Archetype;
struct Equipment;
enum class Ability;

enum class LookDirection
{
	UP, DOWN, LEFT, RIGHT
};

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
	short _burning_turns; float burning_damage;
	short _stunned_turns;  bool  can_fight;

	short __barrier_turns; float barrier_value; float _store_cur_health;
	
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

	LookDirection lookDirection;

	Inventory inventory;
	std::vector<Ability> abilities;
	std::shared_ptr<Archetype> archetype;

	Entity();
	virtual ~Entity() = 0;

	virtual void Behaviour();
	std::string UpdateSideEffects();
	void ApplyEquipedItemStats();
	void ChangeEquipment(std::shared_ptr<Equipment>, bool _shouldEquip = false, bool _hideDialog = true);
	void DrinkPotion(std::shared_ptr<Potion>);
	void UpdateStatus(bool);
	void DisplayStatus();
	void SetLevel(short);
};