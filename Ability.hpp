#pragma once
#include "Player.hpp"
#include "Enemy.hpp"

struct Ability
{
	float damageMultiplier;
	float criticalMultiplier;
	float accuracy;

	Ability();
	~Ability();

	void Use();
};