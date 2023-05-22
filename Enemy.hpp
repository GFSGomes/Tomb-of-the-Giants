#pragma once
#include "Entity.hpp"

struct Light;

struct Enemy : Entity
{
	Sprite sprite;
	short lookX;
	short lookY;

	Enemy(const char*, short, Sprite);
	~Enemy();

	void Behaviour(bool, std::vector<std::shared_ptr<GameObject>>);
};