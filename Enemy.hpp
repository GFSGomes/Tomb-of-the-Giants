#pragma once
#include "Entity.hpp"

struct Enemy : Entity
{
	Enemy(const char*);
	~Enemy();

	void Actions(bool);
};