#pragma once
#include "Miscellaneous.hpp"

enum class KeyType
{
	PORTAL_KEY, SECRET_KEY, CHEST_KEY
};

struct Key : Miscellaneous
{

	KeyType key_type;

	Key(KeyType);
	~Key();
};