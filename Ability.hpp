#pragma once
#include <string>

enum class Skill
{
	ATTACK, POMMEL_STRIKE,
};

struct Ability
{
	Ability();
	~Ability();

	std::string CastAbility(Skill);
};