#include "Player.hpp"
#include "AbilityCast.hpp"
#include "Wall.hpp"
#include "Light.hpp"
#include "Global.hpp"

Player PLAYER("PLAYER");

Player::Player(const char* _name) : isTorchActive{false}, torchDuration{50}, FOV3{16, 17, 18, 23, 25, 30, 31, 32}, FOV7{2, 3, 4, 8, 9,10,11,12,14,15,19,20,21,22,26,27,28,29,33,34,36,37,38,39,40,44,45,46}, FOV7_X{0, 1, 5, 6, 7,13,24,35,41,42,43,47,48}, FOV{}
{
	name = _name;
	CreateFOV();
	UpdateFOV();

	abilities.push_back(Ability::DOUBLE_STRIKE);
	abilities.push_back(Ability::BRUTAL_STRIKE);
	abilities.push_back(Ability::MANA_SHIELD);
}

Player::~Player()
{
	posX = 0;
	posY = 0;
}

void Player::Actions(char input, std::vector<std::shared_ptr<GameObject>> SceneOBJ)
{

	switch (input)
	{
		case 'w': case 'W':
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

		case 's': case 'S':
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

		case 'a': case 'A':
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

		case 'd': case 'D':
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

		case 't': case 'T':
			if (torchDuration > 0)
			{
				isTorchActive = !isTorchActive;
				UpdateFOV();
			}
			break;

		default: return;
	}

	if (isTorchActive)
	{
		torchDuration > 0 ? torchDuration-- : isTorchActive = false;
	}

	UpdateFOV();
}

void Player::CreateFOV()
{
	if (FOV.empty())
	{
		short reserve = (sizeof(FOV3) + sizeof(FOV7) + sizeof(FOV7_X)) / sizeof(short);

		FOV.reserve(reserve); // 49

		for (short i = 0; i < FOV.capacity(); i++)
		{
			FOV.push_back(std::make_shared<Light>());
		}
	}
}

void Player::UpdateFOV()
{
	short width = 7;
	short offset = 3;

	for (short y = -offset; y <= offset; y++)
	{
		for (short x = -offset; x <= offset; x++)
		{
			short index = ((y + offset) * width) + (x + offset);

			FOV[index]->Reposition(posX + x, posY + y);

			if (!isTorchActive)
			{
				for (short i : FOV3)
				{
					if (index == i)
					{
						FOV[index]->proximityReveal = true;
						FOV[index]->active = true;
					}
				}

				for (short i : FOV7)
				{
					if (index == i)
					{
						FOV[index]->active = false;
					}
				}
			}

			else
			{
				for (short i : FOV3)
				{
					if (index == i)
					{
						FOV[index]->proximityReveal = false;
						FOV[index]->active = true;

					}
				}

				for (short i : FOV7)
				{
					if (index == i)
					{
						FOV[index]->active = true;
					}
				}
			}

			for (short i : FOV7_X)
			{
				if (index == i)
				{
					FOV[index]->active = false;
				}
			}
		}
	}
}