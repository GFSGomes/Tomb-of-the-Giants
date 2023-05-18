#pragma once
#include <sstream>
#include <fstream>
#include "Entity.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
struct Entity;

 enum class Ability
 {
	 NONE,
	 ATTACK,
	 DOUBLE_STRIKE,
	 BRUTAL_STRIKE,
	 FIREBALL,
	 MANA_SHIELD,
 };

 enum class Condition
 {
	 HIT, MISS, CRIT, OFM
 };

struct AbilityCast
{
	AbilityCast(){}; // Impede a cria��o de m�ltiplas inst�ncias ?
	~AbilityCast();

	static json GetAbility(Ability);
	static std::string Cast(Ability, std::shared_ptr<Entity>, std::shared_ptr<Entity>);
	static std::string GetAbilityName(Ability);
};