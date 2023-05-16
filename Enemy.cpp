#include "Enemy.hpp"
#include "AbilityCast.hpp"
#include "Global.hpp"
#include "Wall.hpp"

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

void Enemy::Actions(bool _forceMovement, std::vector<std::shared_ptr<GameObject>> SceneOBJ = std::vector<std::shared_ptr<GameObject>>())
{
	short idleness;

	_forceMovement ? idleness = 4 : idleness = 50;

	short direction = rand() % idleness + 1;

	switch (direction)
	{
		case 1:
		{
			if (posY > 0)
			{
				bool canMoveUp = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJ)
				{
					if (std::dynamic_pointer_cast<Wall>(obj))
					{
						if (obj->posX == posX && obj->posY + 1 == posY)
						{
							canMoveUp = false;
							continue;
						}
					}
				}
				if (canMoveUp)
				{
					posY--;
				}
			}
			break;
		}

		case 2:
		{
			if (posY < GridSizeY - 1)
			{
				bool canMoveDown = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJ)
				{
					if (std::dynamic_pointer_cast<Wall>(obj))
					{
						if (obj->posX == posX && obj->posY - 1 == posY)
						{
							canMoveDown = false;
							continue;
						}
					}
				}
				if (canMoveDown)
				{
					posY++;
				}
			}
			break;
		}

		case 3:
		{
			if (posX > 0)
			{
				bool canMoveLeft = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJ)
				{
					if (std::dynamic_pointer_cast<Wall>(obj))
					{
						if (obj->posX + 1 == posX && obj->posY == posY)
						{
							canMoveLeft = false;
							continue;
						}
					}
				}
				if (canMoveLeft)
				{
					posX--;
				}
			}
			break;
		}

		case 4:
		{
			if (posX < GridSizeX - 1)
			{
				bool canMoveRight = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJ)
				{
					if (std::dynamic_pointer_cast<Wall>(obj))
					{
						if (obj->posX - 1 == posX && obj->posY == posY)
						{
							canMoveRight = false;
							continue;
						}
					}
				}
				if (canMoveRight)
				{
					posX++;
				}
			}
			break;
		}
		default:
			break;
	}
}