#pragma once
#include "Ability.hpp"

struct DoubleStrike : Ability
{
	DoubleStrike();
	~DoubleStrike();

	std::string Use(Entity*, Entity*);
};