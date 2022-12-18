#pragma once
#include "Player.hpp"
#include "Enemy.hpp"
#include <sstream>


struct Ability
{
	std::string name;
	std::string description;
	short damage;
	short heal;
	short buff;
	short debuff;
	short requiredAccuracy;
	short cost;

	Ability();
	~Ability();
};