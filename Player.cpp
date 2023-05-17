#include "Player.hpp"
#include "AbilityCast.hpp"
#include "Wall.hpp"
#include "Light.hpp"
#include "Global.hpp"

Player PLAYER("PLAYER");

Player::Player(const char* _name) : isTorchActive{false}, torchDuration{50}, fov_diameter{5}, fov_state{FOV_STATE::OFF}, FOV{}
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

void Player::Behaviour(char input, std::vector<std::shared_ptr<GameObject>> SceneOBJ)
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
		{
			if (torchDuration > 0)
			{
				isTorchActive = !isTorchActive;
				UpdateFOV();
			}
			break;
		}

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
	short index = 0;

	FOV.clear();

	for (short y = 0; y < 10; y++)
	{
		if (y >= fov_diameter)
		{
			break;
		}

		for (short x = 0; x < 10; x++)
		{
			if (x < fov_diameter)
			{
				std::shared_ptr<Light> light = std::make_shared<Light>();
				light->index = index;
				FOV.push_back(light);
			}
			index++;
		}
	}

	for (short i = 0; i < FOV.size(); i++)
	{
		if (fov_diameter == 7)
		{
			// Deletando Corners
			switch (FOV[i]->index)
			{
				case 0: case 6: case 33: case 60: case 66: case 1: case 5: case 10: case 16: case 50: case 56: case 61: case 65:
					FOV.erase(FOV.begin() + i);
					i--; // ! Importante;
					break;
			}

			switch (FOV[i]->index)
			{
				case 22: case 23: case 24: case 32: case 34: case 42: case 43: case 44:
					FOV[i]->candle = true;
					break;
			}
		}
		else if (fov_diameter == 5)
		{
			// Deletando Corners
			switch (FOV[i]->index)
			{
				case 0: case 4: case 22: case 40: case 44: 
					FOV.erase(FOV.begin() + i);
					i--;
					break;

				// Definindo InnerSenses
				case 11: case 12: case 13: case 21: case 23: case 31: case 32: case 33:
					FOV[i]->candle = true;
					break;
			}
		}
	}

	UpdateFOV();

	// 00 01 02 03 04 05 06 07 08 09
	// 10 11 12 13 14 15 16 17 18 19
	// 20 21 22 23 24 25 26 27 28 29
	// 30 31 32 33 34 35 36 37 38 39
	// 40 41 42 43 44 45 46 47 48 49
	// 50 51 52 53 54 55 56 57 58 59
	// 60 61 62 63 64 65 66 67 68 69
	// 70 71 72 73 74 75 76 77 78 79
	// 80 81 82 83 84 85 86 87 88 89
	// 90 91 92 93 94 95 96 97 98 99
}

void Player::UpdateFOV()
{
	if (!isTorchActive)
	{
		if (fov_diameter == 7)
		{
			for (short i = 0; i < FOV.size(); i++)
			{
				switch (FOV[i]->index)
				{
					case 22: case 23: case 24: case 32: case 34: case 42: case 43: case 44:
						FOV[i]->candle = true;
						break;
				}
			}
		}

		if (fov_diameter == 5)
		{
			for (short i = 0; i < FOV.size(); i++)
			{
				switch (FOV[i]->index)
				{
					case 11: case 12: case 13: case 21: case 23: case 31: case 32: case 33:
						FOV[i]->candle = true;
						break;
				}
			}
		}
	}

	//Posicionamento
	for (short i = 0; i < FOV.size(); i++)
	{
		if (fov_diameter == 5)
		{
			switch (FOV[i]->index)
			{
				case 1:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY - 2;
					break;
				case 2:
					FOV[i]->posX = posX;
					FOV[i]->posY = posY - 2;
					break;
				case 3:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY - 2;
					break;
				case 10:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY - 1;
					break;
				case 11:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY - 1;
					break;
				case 12:
					FOV[i]->posX = posX;
					FOV[i]->posY = posY - 1;
					break;
				case 13:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY - 1;
					break;
				case 14:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY - 1;
					break;
				case 20:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY;
					break;
				case 21:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY;
					break;

				case 23:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY;
					break;
				case 24:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY;
					break;
				case 30:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY + 1;
					break;
				case 31:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 1;
					break;
				case 32:
					FOV[i]->posX = posX;
					FOV[i]->posY = posY + 1;
					break;
				case 33:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 1;
					break;
				case 34:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY + 1;
					break;
				case 41:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 2;
					break;
				case 42:
					FOV[i]->posX = posX;
					FOV[i]->posY = posY + 2;
					break;
				case 43:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 2;
					break;
			}
		}
		if (fov_diameter == 7)
		{
			switch (FOV[i]->index)
			{
				case 1:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY - 3;
					break;
				case 2:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY - 3;
					break;
				case 3:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY - 3;
					break;
				case 4:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY - 3;
					break;
				case 5:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY - 3;
					break;


				
				case 10:
					FOV[i]->posX = posX - 3;
					FOV[i]->posY = posY - 2;
					break; 
				case 11:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY - 2;
					break;
				case 12:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY - 2;
					break;
				case 13:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY - 2;
					break;
				case 14:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY - 2;
					break;
				case 15:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY - 2;
					break;
				case 16:
					FOV[i]->posX = posX + 3;
					FOV[i]->posY = posY - 2;
					break;
    

				case 20:
					FOV[i]->posX = posX - 3;
					FOV[i]->posY = posY - 1;
					break;
				case 21:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY - 1;
					break;
				case 22:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY - 1;
					break;
				case 23:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY - 1;
					break;
				case 24:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY - 1;
					break;
				case 25:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY - 1;
					break;
				case 26:
					FOV[i]->posX = posX + 3;
					FOV[i]->posY = posY - 1;
					break;


				case 30:
					FOV[i]->posX = posX - 3;
					FOV[i]->posY = posY + 0;
					break;
				case 31:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY + 0;
					break;
				case 32:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 0;
					break;


				case 34:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 0;
					break;
				case 35:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY + 0;
					break;
				case 36:
					FOV[i]->posX = posX + 3;
					FOV[i]->posY = posY + 0;
					break;


				case 40:
					FOV[i]->posX = posX - 3;
					FOV[i]->posY = posY + 1;
					break;
				case 41:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY + 1;
					break;
				case 42:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 1;
					break;
				case 43:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY + 1;
					break;
				case 44:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 1;
					break;
				case 45:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY + 1;
					break;
				case 46:
					FOV[i]->posX = posX + 3;
					FOV[i]->posY = posY + 1;
					break;

				case 50:
					FOV[i]->posX = posX - 3;
					FOV[i]->posY = posY + 2;
					break;
				case 51:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY + 2;
					break;
				case 52:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 2;
					break;
				case 53:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY + 2;
					break;
				case 54:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 2;
					break;
				case 55:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY + 2;
					break;
				case 56:
					FOV[i]->posX = posX + 3;
					FOV[i]->posY = posY + 2;
					break;



				case 61:
					FOV[i]->posX = posX - 2;
					FOV[i]->posY = posY + 3;
					break;
				case 62:
					FOV[i]->posX = posX - 1;
					FOV[i]->posY = posY + 3;
					break;
				case 63:
					FOV[i]->posX = posX + 0;
					FOV[i]->posY = posY + 3;
					break;
				case 64:
					FOV[i]->posX = posX + 1;
					FOV[i]->posY = posY + 3;
					break;
				case 65:
					FOV[i]->posX = posX + 2;
					FOV[i]->posY = posY + 3;
					break;
			}
		}
	}
}