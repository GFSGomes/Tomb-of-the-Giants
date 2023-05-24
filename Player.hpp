#pragma once
#include "Entity.hpp" // vector e memory

struct Item;
struct Light;

enum class PlayerState
{
	IDLE, MOVING
};

struct Player : Entity 
{
	enum class FovState
	{
		OFF, LOW, HIGH
	};

	short fov_diameter;
	short torchDuration;
	bool isTorchActive;

	FovState fov_state;
	PlayerState state;
	std::vector<std::shared_ptr<Item>> items;
	std::vector<std::shared_ptr<Light>> FOV;
	std::vector<std::shared_ptr<Item>> Inventory;

	Player(const char*);
	~Player();

	char Behaviour(char, std::vector<std::shared_ptr<GameObject>> &SceneOBJs);
	void CreateFOV();
	void UpdateFOV();
	void ManageInventory(std::vector<std::shared_ptr<GameObject>> &SceneOBJs);
};

extern Player PLAYER;