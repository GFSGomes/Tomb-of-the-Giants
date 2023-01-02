#pragma once
#include <sstream>
#include "Entity.hpp"

struct Ability
{
	std::string name;
	std::string description;
	float cost;
	float baseBonus;
	float bonusMultiplier;
	float requiredAccuracy;

	Ability();
	virtual ~Ability() = 0;

	virtual std::string Cast(std::shared_ptr<Entity>, std::shared_ptr<Entity>);
};