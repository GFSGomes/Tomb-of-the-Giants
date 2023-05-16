#pragma once
#include "GameObject.hpp"
#include <vector>
#include <memory>

struct Wall : GameObject
{
	Wall(short, short);
	~Wall();
};