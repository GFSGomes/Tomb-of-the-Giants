#pragma once
#include "Item.hpp";

enum class PotionType
{
	MINOR_HEALTH_POTION, 
	MEDIUM_HEALTH_POTION, 
	GREAT_HEALTH_POTION,

	MINOR_MANA_POTION,
	MEDIUM_MANA_POTION,
	GREAT_MANA_POTION,
};

struct Potion : Item
{
	PotionType potionType;
	float health_recovery;
	float mana_recovery;

	Potion(const char*, PotionType);
	~Potion();
};