#pragma once
#include "GameObject.hpp"

struct Light : GameObject
{
	bool candle;
	short index;

	Light();
	~Light();
};