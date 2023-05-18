#pragma once
#include "Item.hpp"

enum class KeyType
{
	PORTAL_KEY, SECRET_KEY, CHEST_KEY
};

struct Key : Item
{

	KeyType key_type;

	Key(KeyType);
	~Key();
};