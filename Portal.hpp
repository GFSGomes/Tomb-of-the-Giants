#pragma once
#include "GameObject.hpp"

struct Scene;

struct Portal : GameObject
{
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Portal> out;

	Portal(short, short);
	~Portal();
};