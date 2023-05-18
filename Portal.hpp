#pragma once
#include "GameObject.hpp"
#include "Key.hpp"

struct Scene;

struct Portal : GameObject
{
	bool is_locked;

	KeyType key_type;

	std::shared_ptr<Portal> mirror;

	std::shared_ptr<Scene> origin;
	std::shared_ptr<Scene> destiny;


	Portal(short, short, std::shared_ptr<Scene>, std::shared_ptr<Scene>, bool _is_locked = false, KeyType _key_type = KeyType::PORTAL_KEY);
	~Portal();
};