#pragma once
#include "GameObject.hpp"

struct Entity : GameObject {

	float health;
	float damage;
	bool alive;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
};