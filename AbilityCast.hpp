#pragma once
#include <sstream>
#include <fstream>
#include "Entity.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
struct Entity;

 enum class Ability
 {
	 ATTACK,
	 DOUBLE_STRIKE,
 };

struct AbilityCast
{
	AbilityCast(){}; // Impede a criação de múltiplas instâncias ?
	~AbilityCast();

	static json GetAbility(Ability);
	static std::string Cast(Ability, std::shared_ptr<Entity>, std::shared_ptr<Entity>);
	static std::string GetAbilityName(Ability);
};