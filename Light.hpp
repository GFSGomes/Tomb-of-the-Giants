#pragma once
#include "GameObject.hpp"

struct Light : GameObject
{
	bool near;
	short index;

	Light();
	~Light();
};