#pragma once
#include "Equipment.hpp"
#include "Ability.hpp"

struct Weapon : Equipment
{
	std::vector<std::shared_ptr<Ability>> Skill;

	Weapon(const char*);
	virtual ~Weapon() = 0;
};