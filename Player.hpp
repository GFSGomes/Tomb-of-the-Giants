#pragma once
#include "Entity.hpp" // vector e memory

struct Item;
struct Light;
//struct GameObject;

struct Player : Entity 
{
	enum class FOV_STATE
	{
		OFF, LOW, HIGH
	};

	short fov_diameter;
	short torchDuration;
	bool isTorchActive;

	FOV_STATE fov_state;
	std::vector<std::shared_ptr<Item>> items;
	std::vector<std::shared_ptr<Light>> FOV;
	std::vector<std::shared_ptr<Item>> Inventory;

	Player(const char*);
	~Player();

	void Behaviour(char, std::vector<std::shared_ptr<GameObject>>);
	void CreateFOV();
	void UpdateFOV();
};

extern Player PLAYER;