#include "Grid.hpp"
#include "Light.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Equipment.hpp"
#include "Global.hpp"
#include "Wall.hpp"
#include "Portal.hpp"

//struct Portal;
short GridSizeX = 0;
short GridSizeY = 0;

Grid::Grid(short _sizeX, short _sizeY) : secret_portal_reveal{false}, sizeX{_sizeX}, sizeY{_sizeY}
{
	GridSizeX = sizeX;
	GridSizeY = sizeY;
}

Grid::~Grid()
{

}

void Grid::UpdateGrid(std::vector<std::shared_ptr<GameObject>> SceneOBJs, std::shared_ptr<Player> player)
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

			for (short i = 0; i < SceneOBJs.size(); i++)
			{
				if (SceneOBJs[i]->posY == y && SceneOBJs[i]->posX == x)
				{
					count = i;

					// Light
					if (std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(SceneOBJs[i]))
					{
						if (light->active)
						{
							if (light->near) // Antigo proximityReveal
							{
								icon = " ";  // Unicode
							}

							if (player->isTorchActive)
							{
								CompatibilityMode ?
								icon = "." : // Ascii
								icon = "·";  // Unicode
							}

							for (short j = 0; j < SceneOBJs.size(); j++)
							{
								if (std::shared_ptr<Wall> wall = std::dynamic_pointer_cast<Wall>(SceneOBJs[j]))
								{
									if (wall->posX == light->posX && wall->posY == light->posY)
									{
										if (light->near)
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

								if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJs[j]))
								{
									if (item->posX == light->posX && item->posY == light->posY)
									{
										 /* Items - Tocha Acesa */

										if (light->near)
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

								if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJs[j]))
								{
									if (enemy->posX == light->posX && enemy->posY == light->posY)
									{
										 /* Monstro - Tocha Acesa */

										if (light->near)
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

								if (std::shared_ptr<Player> _player = std::dynamic_pointer_cast<Player>(SceneOBJs[j]))
								{
									if (_player->posX == light->posX && _player->posY == light->posY)
									{
										if (light->near)
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
										break;
									}
								}
								
								if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(SceneOBJs[j]))
								{
									if (portal->posX == light->posX && portal->posY == light->posY)
									{
										if (portal->isLocked)
										{
											if (light->near)
											{
												CompatibilityMode ?
													icon = ":" :
													icon = "♦";
											
												// Caso trancado, nunca deve ser revelado:
												if (portal->keyType == KeyType::SECRET_KEY)
												{
													icon = " ";
												}
											}

											if (player->isTorchActive || DebugMode)
											{
												CompatibilityMode ?
													icon = ":" :
													icon = "♦";

												// Caso trancado, nunca deve ser revelado:
												if (portal->keyType == KeyType::SECRET_KEY)
												{
													CompatibilityMode ?
														icon = "." : // Ascii
														icon = "·";  // Unicode
												}
											}
											
										}
										else
										{
											if (light->near)
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
						break; // Impede a prioridade da escuridão
					}
					
					#pragma region DarknessObjectRendering
					if (std::dynamic_pointer_cast<Wall>(SceneOBJs[i]))
					{
						if (DebugMode)
						{
							CompatibilityMode ?
								icon = "#" :
								icon = "■";
						}
					}

					if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJs[i]))
					{
						if (SceneOBJs[i]->active)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "i" :
									icon = "▴";
							}
						}
					}

					if (std::dynamic_pointer_cast<Enemy>(SceneOBJs[i]))
					{
						if (SceneOBJs[i]->active)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "M" :
									icon = "○";
							}
						}
						break;
					}

					if (std::dynamic_pointer_cast<Player>(SceneOBJs[i]))
					{
						CompatibilityMode ?
							icon = "P" :
							icon = "●";
						break;
					}

					if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(SceneOBJs[i]))
					{
						if (portal->isLocked)
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = ":":
									icon = "♦";
							}
						}
						else
						{
							if (DebugMode)
							{
								CompatibilityMode ?
									icon = "p" :
									icon = "◊";
							}
						}

						if (portal->keyType == KeyType::SECRET_KEY)
						{
							icon = " ";
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