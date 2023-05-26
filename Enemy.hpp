#pragma once
#include "Entity.hpp"

struct Light;
struct Item;

struct Enemy : Entity
{
	Sprite sprite;
	short lookX;
	short lookY;

	std::vector <std::shared_ptr<Item>> drops;
	Enemy(const char*, short, Sprite);
	~Enemy();

	void Behaviour(bool, std::vector<std::shared_ptr<GameObject>>);
	std::vector<std::shared_ptr<Item>> DropItem();
};