#pragma once
#include "Entity.hpp"

struct Enemy : Entity
{
	Enemy(const char*, short, Sprite);

	~Enemy();

	void Actions(bool);
};