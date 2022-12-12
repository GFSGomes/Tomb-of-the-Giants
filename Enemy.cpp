#include "Enemy.hpp"

Enemy::Enemy(const char* _name)
{
	strcpy_s(name,_name);
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