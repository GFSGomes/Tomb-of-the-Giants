#pragma once
#include "Entity.hpp"

struct Enemy : Entity
{
	Sprite sprite;

	Enemy(const char*, short, Sprite);

	~Enemy();

	void Behaviour(bool, std::vector<std::shared_ptr<GameObject>>);
};