#pragma once
#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"

extern short GridSizeX;
extern short GridSizeY;

struct Grid
{
	short sizeX;
	short sizeY;

	Grid(short,short);
	~Grid();

	void UpdateGrid(std::vector<std::shared_ptr<GameObject>>, std::shared_ptr<Player>);
};