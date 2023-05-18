#include "Grid.hpp"
#include "Light.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Equipment.hpp"
#include "Portal.hpp"
#include "Global.hpp"
#include "Wall.hpp"

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

	for (short y = 0; y <= sizeY; y++)
	{
		#pragma region GRID_LEFT
		CompatibilityMode ?
			std::cout << " | ":
			std::cout << " │ ";
		#pragma endregion

		for (short x = 0; x <= sizeX; x++)
		{
			short count = -1;
			std::string icon = "\0";

			for (short i = 0; i < SceneOBJ.size(); i++)
			{
				if (SceneOBJ[i]->posY == y && SceneOBJ[i]->posX == x)
				{
					count = i;

					// Light
					if (std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(SceneOBJ[i]))
					{
						if (light->active)
						{
							if (light->candle) // Antigo proximityReveal
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
								if (std::shared_ptr<Wall> wall = std::dynamic_pointer_cast<Wall>(SceneOBJ[j]))
								{
									if (wall->posX == light->posX && wall->posY == light->posY)
									{
										if (light->candle)
										{
											CompatibilityMode ?
												icon = "#" :
												icon = "■";
										}

										if (player->isTorchActive || DebugMode)
										{
											CompatibilityMode ?
												icon = "#" :
												icon = "■";
										}
									}
								}

								if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[j]))
								{
									if (item->posX == light->posX && item->posY == light->posY)
									{
										 /* Items - Tocha Acesa */

										if (light->candle)
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

								if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[j]))
								{
									if (enemy->posX == light->posX && enemy->posY == light->posY)
									{
										 /* Monstro - Tocha Acesa */

										if (light->candle)
										{
											CompatibilityMode ?
												icon = "M" :
												icon = "○";
										}

										if (player->isTorchActive || DebugMode)
										{
											CompatibilityMode ?
												icon = "M" :
												icon = "○";
										}
									}
								}

								if (std::shared_ptr<Player> _player = std::dynamic_pointer_cast<Player>(SceneOBJ[j]))
								{
									if (_player->posX == light->posX && _player->posY == light->posY)
									{
										if (light->candle)
										{
											CompatibilityMode ?
												icon = "P" :
												icon = "●";
										}

										if (player->isTorchActive || DebugMode)
										{
											CompatibilityMode ?
												icon = "P" :
												icon = "●";
										}
									}
								}
								
								if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(SceneOBJ[j]))
								{
									if (portal->posX == light->posX && portal->posY == light->posY)
									{
										if (portal->is_locked) 
										{
											if (light->candle)
											{
												CompatibilityMode ?
													icon = ":" :
													icon = "♦";
											}

											if (player->isTorchActive || DebugMode)
											{
												CompatibilityMode ?
													icon = ":" :
													icon = "♦";

												if (portal->key_type == KeyType::SECRET_KEY) // Visible only on proximity_reveal
												{
													CompatibilityMode ?
														icon = "." : // Ascii
														icon = "·";  // Unicode

													/*if (DebugMode)
													{
														CompatibilityMode ?
															icon = ":" :
															icon = "♦";
													}*/
												}
											}

										}
										else
										{
											if (light->candle)
											{
												CompatibilityMode ?
													icon = "D" :
													icon = "◊";
											}

											if (player->isTorchActive || DebugMode)
											{
												CompatibilityMode ?
													icon = "D" :
													icon = "◊";
											}
										}
									}
								}
							}
						}
					}
					#pragma region DarknessObjectRendering

					// A disposição afeta prioridade de renderização:
					if (std::dynamic_pointer_cast<Wall>(SceneOBJ[i]))
					{
						if (DebugMode)
						{
							CompatibilityMode ?
								icon = "#" :
								icon = "■";
						}
					}

					if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[i]))
					{
						if (SceneOBJ[i]->active)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "i" :
									icon = "▴";
							}
						}
					}

					if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(SceneOBJ[i]))
					{
						if (portal->is_locked)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = ";":
									icon = "♦";
							}
						}
						else
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "D" :
									icon = "◊";
							}
						}
					}

					if (std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
					{
						if (SceneOBJ[i]->active)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "M" :
									icon = "○";
							}
						}
					}

					if (std::dynamic_pointer_cast<Player>(SceneOBJ[i]))
					{
						CompatibilityMode ?
							icon = "P" :
							icon = "●";
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