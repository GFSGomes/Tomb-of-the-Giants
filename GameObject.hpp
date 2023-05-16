#pragma once
#include <iostream>

enum class Sprite;

struct GameObject 
{
	short posX;
	short posY;
	bool active;
	std::string name;
	std::string description;
	Sprite sprite;

	GameObject();
	virtual ~GameObject() = 0;

	void SpawnAt(short, short);
	void SpawnRandom();
};