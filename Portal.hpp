#pragma once
#include "GameObject.hpp"
#include "Key.hpp"

struct Scene;

enum class Position
{
	UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT, CENTER, OTHER
};

struct Portal : GameObject
{
	bool isLocked;
	bool secretReveal;
	std::shared_ptr<Scene> scene;   // Destiny scene to be loaded;
	std::shared_ptr<Portal> mirror; // Destiny portal - defines player spawn point in the next scene;
	KeyType keyType;
	Position position;

	Portal(Position, std::shared_ptr<Scene>, bool isLocked = false, KeyType keyType = KeyType::PORTAL_KEY, short _posX = 0, short _posY = 0);
	~Portal();
	void SearchMirrorInDestiny();
};