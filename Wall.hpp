#pragma once
#include "GameObject.hpp"
#include <vector>
#include <memory>

enum class WallDirection
{
	HORIZONTAL, VERTICAL
};
struct Wall : GameObject
{
	WallDirection direction;
	std::vector < std::shared_ptr<Wall>> bricks;

	Wall(short _startX = 0, short _startY = 0);
	Wall(WallDirection _walldirection, short _startX = -1 , short _startY = -1, short _lenght = 0);
	~Wall();
};