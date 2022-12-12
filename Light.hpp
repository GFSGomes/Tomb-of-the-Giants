#pragma once
#include "GameObject.hpp"

struct Light : GameObject
{
	bool proximityReveal;
	Light();
	~Light();

	void Reposition(short, short);
};