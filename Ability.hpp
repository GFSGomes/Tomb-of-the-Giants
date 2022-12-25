#pragma once
#include <string>

struct Ability
{
	short cost;

	Ability();
	virtual ~Ability() = 0;

	virtual std::string Use();
};