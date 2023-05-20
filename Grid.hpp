#pragma once
#include <vector>
#include <memory>

struct GameObject;
struct Player;

struct Grid
{
	short sizeX;
	short sizeY;

	bool secret_portal_reveal;

	Grid(short,short);
	~Grid();

	void UpdateGrid(std::vector<std::shared_ptr<GameObject>>, std::shared_ptr<Player>);
};