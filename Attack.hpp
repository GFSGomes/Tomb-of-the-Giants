#pragma once
#include "Ability.hpp"

struct Attack : Ability
{
	Attack();
	~Attack();

	std::string Cast(std::shared_ptr<Entity>, std::shared_ptr<Entity>) override;
};