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
	/*std::cout << "   ┌";
	for (short i = 0; i < GridSizeX; i++)
	{std::cout << "──";}
	std::cout << "─┐   ";
	std::cout << "\n";*/
	std::cout << "   -";
	for (short i = 0; i < GridSizeX; i++)
	{std::cout << "--";}
	std::cout << "--   ";
	std::cout << "\n";

	for (short y = 0; y < sizeY; y++)
	{
		//std::cout << "   │ ";
		std::cout << "   | ";

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
								//icon = "·";
								icon = ".";
							}

							for (short j = 0; j < SceneOBJ.size(); j++)
							{
								if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[j]))
								{
									if (enemy->posX == fov->posX && enemy->posY == fov->posY)
									{
										if (fov->proximityReveal)
										{
											icon = "x";
										}
										if (player->isTorchActive)
										{
											//icon = "○";
											icon = "M";
										}

										if (DebugMode)
										{
											icon = "M";
										}
									}
								}

								if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[j]))
								{
									if (item->posX == fov->posX && item->posY == fov->posY)
									{
										if (fov->proximityReveal)
										{
											if (DebugMode)
											{
												icon = "i";
											}
											else
											{
												icon = "x";
											}
										}

										if (player->isTorchActive)
										{
											if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(SceneOBJ[j]))
											{
												icon = "e";
											}
											else
											{
												icon = "i";
											}
										}
									}
								}
							}
						}
					}

					// Darkness
					if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(SceneOBJ[i]))
					{
						//icon = "●";
						icon = "P";
					}

					if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
					{
						if (enemy->active)
						{
							if (DebugMode) // DEBUG
							{
								icon = "M";
							}
						}
					}

					if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[i]))
					{
						if (item->active)
						{
							if (DebugMode)
							{
								icon = "i";
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
		//std::cout << "│\n";
		std::cout << "|\n";
	}

	/*std::cout << "   └";
	for (short i = 0; i < GridSizeX; i++)
	{std::cout << "──";}
	std::cout << "─┘   ";*/
	std::cout << "   -";
	for (short i = 0; i < GridSizeX; i++)
	{std::cout << "--";}
	std::cout << "--   ";
}