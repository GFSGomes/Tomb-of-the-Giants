#pragma once
#include "Entity.hpp"
#include "Light.hpp"
#include <vector>

struct Player : Entity 
{
	short torchDuration;
	bool isTorchActive;

	short FOV3[8];
	short FOV7[28];
	short FOV7_X[13];
	std::vector<std::shared_ptr<Item>> items;
	std::vector<std::shared_ptr<Light>> FOV;
	std::vector<std::shared_ptr<Item>> Inventory;

	Player(const char*);
	~Player();

	void Actions(char);
	void CreateFOV();
	void UpdateFOV();
};

extern Player PLAYER;