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
	#pragma region GRID_TOP
	if (CompatibilityMode)
	{
		std::cout << " .-";
		for (short i = 0; i < GridSizeX; i++)
		{
			std::cout << "--";
		}
		std::cout << ".";
		std::cout << "\n";
	}
	else
	{
		std::cout << " ┌─";
		for (short i = 0; i < GridSizeX; i++)
		{
			std::cout << "──";
		}
		std::cout << "┐";
		std::cout << "\n";
	}
	#pragma endregion

	for (short y = 0; y < sizeY; y++)
	{
		#pragma region GRID_LEFT
		CompatibilityMode ?
			std::cout << " | ":
			std::cout << " │ ";
		#pragma endregion

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
								icon = " ";  // Unicode
							}

							if (player->isTorchActive)
							{
								CompatibilityMode ?
								icon = "." : // Ascii
								icon = "·";  // Unicode
							}

							for (short j = 0; j < SceneOBJ.size(); j++)
							{
								if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[j]))
								{
									if (enemy->posX == fov->posX && enemy->posY == fov->posY)
									{
										 /* Monstro - Tocha Acesa */

										if (fov->proximityReveal)
										{
											CompatibilityMode ?
											icon = "E" :
											icon = "○";
										}

										if (player->isTorchActive || DebugMode)
										{
											CompatibilityMode ?
											icon = "E":
											icon = "○";
										}
									}
								}

								if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[j]))
								{
									if (item->posX == fov->posX && item->posY == fov->posY)
									{
										 /* Items - Tocha Acesa */

										if (fov->proximityReveal)
										{
											CompatibilityMode ?
											icon = "i" :
											icon = "▴";
										}

										if (player->isTorchActive || DebugMode)
										{
											CompatibilityMode ?
											icon = "i" :
											icon = "▴";
										}
									}
								}
							}
						}
					}
					#pragma region DarknessObjectRendering

					if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(SceneOBJ[i]))
					{
						CompatibilityMode ?
						icon = "P" :
						icon = "●";
					}

					if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
					{
						if (enemy->active)
						{
							if (DebugMode) // DEBUG
							{
								CompatibilityMode ?
								icon = "M":
								icon = "○";
							}
						}
					}

					if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[i]))
					{
						if (item->active)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "i" :
									icon = "▴";
							}
						}
					}

					#pragma endregion
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
		#pragma region GRID_LEFT
		CompatibilityMode ?
			std::cout << "|" << "\n" :
			std::cout << "│" << "\n";
		#pragma endregion
	}
	#pragma region GRID_BOTTOM
	if (CompatibilityMode)
	{
		std::cout << " '-";
		for (short i = 0; i < GridSizeX; i++)
		{
			std::cout << "--";
		}
		std::cout << "'";
	}
	else
	{
		std::cout << " └─";
		for (short i = 0; i < GridSizeX; i++)
		{
			std::cout << "──";
		}
		std::cout << "┘";
	}
	#pragma endregion
}