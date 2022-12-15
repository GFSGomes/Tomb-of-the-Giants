#pragma once
#include "GameObject.hpp"

struct Entity : GameObject {

	float health;
	float maxHealth;
	float mana;
	float maxMana;

	float physical_pwr;
	float physical_def;
	
	float magical_pwr;
	float magical_def;

	float accuracy;
	float flee;

	bool alive;

	Entity();
	virtual ~Entity() = 0;

	virtual void Actions();
};