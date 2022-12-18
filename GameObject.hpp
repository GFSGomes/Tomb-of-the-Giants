#pragma once
#include "Common.hpp"
#include "Renderer.hpp"

struct GameObject {

	char name[33];
	short posX;
	short posY;
	bool active;
	Sprite sprite;

	GameObject();
	virtual ~GameObject() = 0;

	void SpawnAt(short, short);
	void SpawnRandom();
};