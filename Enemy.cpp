#include "Enemy.hpp"
#include "AbilityCast.hpp"
#include "Global.hpp"
#include "Light.hpp"
#include "ItemDatabase.hpp" // Weapon, Armor, Potion, Key, Torch

Enemy::Enemy(const char* _name, short _level, Sprite _sprite) : sprite{_sprite}, lookX{posX + 1}, lookY{posY}
{
	name = _name;

	level = _level - 1;

	STR = CON = INT = AGI = DEX = level;

	std::shared_ptr<Armor> body = std::make_shared<Armor>(heavyBody_ironPlate);
	std::shared_ptr<Armor> head = std::make_shared<Armor>(heavyHead_bascinet);
	std::shared_ptr<Armor> legs = std::make_shared<Armor>(heavyLegs_greaves);
	std::shared_ptr<Armor> arms = std::make_shared<Armor>(heavyArms_steelGaunlets);
	body->equiped = true;
	head->equiped = true;
	legs->equiped = true;
	arms->equiped = true;

	inventory.AddItem(body);
	inventory.AddItem(head);
	inventory.AddItem(legs);
	inventory.AddItem(arms);

	UpdateStatus(true); // Também chama -> ApplyEquipedItemStats()
}

Enemy::~Enemy()
{

}

void Enemy::Behaviour(bool _forceMovement, std::vector<std::shared_ptr<GameObject>> SceneOBJs)
{
	short idleness{0};

	_forceMovement ? idleness = 4 : idleness = 20;

	short direction = rand() % idleness + 1;
	
	switch (direction)
	{
		case 1:
		{
			if (posY > 0)
			{
				bool canMoveUp = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJs)
				{
					if (!std::dynamic_pointer_cast<Light>(obj))
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

				lookDirection = LookDirection::UP;
				lookX = posX;
				lookY = posY - 1;
			}
			break;
		}
		case 2:
		{
			if (posY < GridSizeY - 1)
			{
				bool canMoveDown = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJs)
				{
					if (!std::dynamic_pointer_cast<Light>(obj))
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
				lookDirection = LookDirection::DOWN; 
				lookX = posX;
				lookY = posY + 1;
			}
			break;
		}
		case 3:
		{
			if (posX > 0)
			{
				bool canMoveLeft = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJs)
				{
					if (!std::dynamic_pointer_cast<Light>(obj))
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
				lookDirection = LookDirection::LEFT;
				lookX = posX - 1;
				lookY = posY;
			}
			break;
		}
		case 4:
		{
			if (posX < GridSizeX - 1)
			{
				bool canMoveRight = true;

				for (std::shared_ptr<GameObject> obj : SceneOBJs)
				{
					if (!std::dynamic_pointer_cast<Light>(obj))
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
				lookDirection = LookDirection::RIGHT;
				lookX = posX + 1;
				lookY = posY;
			}
			break;
		}
		default:
			break;
	}
}

std::vector<std::shared_ptr<Item>> Enemy::DropItem()
{
	return {};
}