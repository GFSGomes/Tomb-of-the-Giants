#pragma once
#include "Ability.hpp"

struct Attack : Ability
{
	Attack();
	~Attack();

	std::string Use(std::shared_ptr<Entity>,std::shared_ptr<Entity>);
};