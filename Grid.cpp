#include "Grid.hpp"

short GridSizeX = 0;
short GridSizeY = 0;

Grid::Grid(short _sizeX, short _sizeY) : sizeX{_sizeX}, sizeY{_sizeY}
{
	GridSizeX = sizeX;
	GridSizeY = sizeY;
}

Grid::~Grid()
{

}

void Grid::UpdateGrid(std::vector<std::shared_ptr<GameObject>> SceneOBJ, std::shared_ptr<Player> player)
{
	for (short y = 0; y < sizeY; y++)
	{
		std::cout << "   |";

		for (short x = 0; x < sizeX; x++)
		{
			short count = -1;
			std::string icon = "\0";

			for (short i = 0; i < SceneOBJ.size(); i++)
			{
				if (SceneOBJ[i]->posY == y && SceneOBJ[i]->posX == x)
				{
					count = i;

					// Light
					if (std::shared_ptr<Light> fov = std::dynamic_pointer_cast<Light>(SceneOBJ[i]))
					{
						if (fov->active)
						{
							if (fov->proximityReveal)
							{
								icon = ' ';
							}
							if (player->isTorchActive)
							{
								icon = '.';
							}

							for (short j = 0; j < SceneOBJ.size(); j++)
							{
								if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[j]))
								{
									if (enemy->posX == fov->posX && enemy->posY == fov->posY)
									{
										if (fov->proximityReveal)
										{
											icon = "○";
										}
										if (player->isTorchActive)
										{
											icon = "●";
										}
									}
								}

								if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[j]))
								{
									if (item->posX == fov->posX && item->posY == fov->posY)
									{
									
									}
								}
							}
						}
					}

					// Darkness
					if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(SceneOBJ[i]))
					{
						if (player->isTorchActive)
						{
							icon = "■";
						}
						else
						{
							icon = "□";
						}
					}

					if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
					{
						if (enemy->alive)
						{
							if (DebugMode) // DEBUG
							{
								icon = "?";
							}
						}
					}

					if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[i]))
					{
						if (item->active)
						{
							if (DebugMode)
							{
								icon = "!";
							}
						}
					}
				}

			}
			if (count >= 0)
			{
				if (icon != "\0")
				{
					std::cout << icon << ' ';
				}
				else
				{
					std::cout << "  ";
				}
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "|\n";
	}
}