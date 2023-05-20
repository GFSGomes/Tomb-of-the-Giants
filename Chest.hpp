#pragma once
#include "GameObject.hpp"
#include "Inventory.hpp"

enum class KeyType;
struct Item;
struct Player;

struct Chest : GameObject
{
	KeyType keyType;
	Inventory inventory;

	Chest();
	~Chest();

	std::shared_ptr<Item> GiveItem(std::shared_ptr<Player>);
};