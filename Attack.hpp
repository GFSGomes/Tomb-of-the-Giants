#pragma once
#include "Ability.hpp"

struct Attack : Ability
{

	Attack();
	~Attack();

	std::string Use(Entity*, Entity*);
};