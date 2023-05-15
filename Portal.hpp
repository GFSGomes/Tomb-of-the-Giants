#pragma once
#include "GameObject.hpp"

struct Scene;

struct Portal : GameObject
{
	std::shared_ptr<Scene> scene;

	Portal(short, short);
	~Portal();
};