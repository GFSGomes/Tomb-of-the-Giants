#pragma once
#include "Consumable.hpp"

enum class PotionType
{
	MINOR_HEALTH_POTION, 
	MEDIUM_HEALTH_POTION, 
	GREATER_HEALTH_POTION,

	MINOR_MANA_POTION,
	MEDIUM_MANA_POTION,
	GREATER_MANA_POTION,
};

struct Potion : Consumable
{
	PotionType potionType;
	short health_recovery;
	short mana_recovery;

	Potion(PotionType);
	~Potion();
};