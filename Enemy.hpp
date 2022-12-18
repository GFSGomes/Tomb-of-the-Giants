#pragma once
#include "Entity.hpp"

struct Enemy : Entity
{
	Enemy(const char*, short);

	~Enemy();

	void Actions(bool);
};