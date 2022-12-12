#pragma once
#include "GameObject.hpp"

struct Item : GameObject
{
	Item();
	virtual ~Item() = 0;

	virtual void Use();
};