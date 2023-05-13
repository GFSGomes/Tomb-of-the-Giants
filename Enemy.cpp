#include "Enemy.hpp"

Enemy::Enemy(const char* _name, short _level, Sprite _sprite) : sprite{_sprite}
{
	name = _name;

	level = _level - 1;

	STR = CON = INT = AGI = DEX = level;

	UpdateStatus(true);
}

Enemy::~Enemy()
{

}

void Enemy::Actions(bool _forceMovement)
{
	short idleness;

	_forceMovement ? idleness = 4 : idleness = 50;

	short direction = rand() % idleness + 1;

	switch (direction)
	{
		case 1: 
			if (posY > 0) posY--;
			break;
		case 2: 
			if (posY < GridSizeY - 1) posY++;
			break;
		case 3: 
			if (posX > 0) posX--;
			break;
		case 4: 
			if (posX < GridSizeX - 1) posX++;
			break;
		default:
			break;
	}
}