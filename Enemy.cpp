#include "Enemy.hpp"

Enemy::Enemy(const char* _name, short _level, Sprite _sprite) : sprite{_sprite}
{
	name = _name;

	level = _level - 1;

	CON = INT = RES = WIS = DEX = level;

	UpdateStatus(true);
}

Enemy::~Enemy()
{

}

void Enemy::Actions(bool _forceMovement)
{
	short idleness;

	_forceMovement ? idleness = 4 : idleness = 50;

	switch (idleness)
	{
		case 0: 
			if (posY < 0) posY--; 
			break;
		case 1: 
			if (posY > GridSizeY - 1) posY++;
			break;
		case 2: 
			if (posX < 0) posX--;
			break;
		case 3: 
			if (posX > GridSizeX - 1) posX++; 
			break;
		default:
			break;
	}
}