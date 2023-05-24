#include "GameInterfaceUI.hpp"
#include "GameSettingsUI.hpp"
#include "Global.hpp"
#include <iostream>
#include <conio.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Renderer.hpp"
#include <windows.h>

GameInterfaceUI UI_GameInterface;
bool IsPaused = false;

GameInterfaceUI::GameInterfaceUI() : _resources_manip{true}, _exp_manip{true}, _level_manip{true}, _torch_manip{true}{}

GameInterfaceUI::~GameInterfaceUI()
{

}

bool GameInterfaceUI::Initialize()
{
	return active;
}

bool GameInterfaceUI::Initialize(std::shared_ptr<Player> player)
{
	system("cls");

	if (active)
	{
		DebugMode ?
		std::cout << " | |Esc| GAME MENU : Game Paused - Debug Mode |" << "\n" :
		std::cout << " | |Esc| GAME MENU : Game Paused              |" << "\n";

		std::cout << " | ------------------------------------------ |" << "\n" ;

		switch (index)
		{
			case 0:
			{
				std::cout << " | > Character                            |C| |" << "\n";
				std::cout << " |   Abilities                            |K| |" << "\n";
				std::cout << " |   Inventory                            |I| |" << "\n";
				std::cout << " |   Settings                             |O| |" << "\n";
				std::cout << " |   Exit Game                                |" << "\n";
				break;
			}				   
							   
			case 1:			   
			{	
				std::cout << " |   Character                            |C| |" << "\n";
				std::cout << " | > Abilities                            |K| |" << "\n";
				std::cout << " |   Inventory                            |I| |" << "\n";
				std::cout << " |   Settings                             |O| |" << "\n";
				std::cout << " |   Exit Game                                |" << "\n";

				break;
			}				   
							   
			case 2:			   
			{				   
				std::cout << " |   Character                            |C| |" << "\n";
				std::cout << " |   Abilities                            |K| |" << "\n";
				std::cout << " | > Inventory                            |I| |" << "\n";
				std::cout << " |   Settings                             |O| |" << "\n";
				std::cout << " |   Exit Game                                |" << "\n";
				break;
			}				   
							   
			case 3:			   
			{				   
				std::cout << " |   Character                            |C| |" << "\n";
				std::cout << " |   Abilities                            |K| |" << "\n";
				std::cout << " |   Inventory                            |I| |" << "\n";
				std::cout << " | > Settings                             |O| |" << "\n";
				std::cout << " |   Exit Game                                |" << "\n";
				break;
			}				   
							   
			case 4:			   
			{				   
				std::cout << " |   Character                            |C| |" << "\n";
				std::cout << " |   Abilities                            |K| |" << "\n";
				std::cout << " |   Inventory                            |I| |" << "\n";
				std::cout << " |   Settings                             |O| |" << "\n";
				std::cout << " | > Exit Game - No one like cowards.         |" << "\n";
				break;
			}

			default: break;
		}
		std::cout << " '--------------------------------------------'" << "\n";
	}
	else
	{
		DebugMode ?
		std::cout << " | |Esc| GAME MENU - DebugMode                |" << "\n" :
		std::cout << " | |Esc| GAME MENU                            |" << "\n";
		std::cout << " '--------------------------------------------'" << "\n" ;
	}
	std::cout << "\n";

	std::cout << " | " << player->name <<" (Lvl. " << player->level << ")" << "\n";
	Renderer::StatusBar("HP", player->cur_health, player->max_health);
	Renderer::StatusBar("MP", player->cur_mana, player->max_mana);
	Renderer::StatusBar("XP", player->cur_experience, player->max_experience);
	return active;
}

char GameInterfaceUI::Input(std::shared_ptr<Player> player, std::vector<std::shared_ptr<GameObject>> &SceneOBJs, short _inputDelay)
{
	std::cout << "\n";
	std::cout << "\n";

	if (player->isTorchActive)
	{
		std::cout << "   |W|   To     |T| Torch [X] " << player->torchDuration << "\n";
		std::cout << " |A|S|D| Move" << "\n";
	}
	else
	{
		std::cout << "   |W|   To     |T| Torch [ ] " << player->torchDuration << "\n";
		std::cout << " |A|S|D| Move" << "\n";
	}

	std::cout << "\n";

	if (DebugMode)
	{
		if (_resources_manip)
		{
			std::cout << " |Rtrn| Increasing (<  ) Decreasing" << "\n";
			std::cout << " |1| (HP/MP)++       | |3| Level UP" << "\n";
			std::cout << " |2| Exp++           | |4| Torch++" << "\n";
		}
		else
		{
			std::cout << " |Rtrn| Increasing (  >) Decreasing" << "\n";
			std::cout << " |1| (HP/MP)--       | |3| Level = 0" << "\n";
			std::cout << " |2| Exp = 0         | |4| Torch--" << "\n";
		}
	}

	Sleep(_inputDelay);

	input = _getch();

	if (active)
	{
		switch (input)
		{
			case 27: 
				IsPaused = false;
				active = false;
				break;
			
			case 'w': case 'W': 
				if (index > 0) index--;
				break;

			case 's': case 'S':
				if (index < 4) index++;
				break;

			case 'c': case 'C': player->DisplayStatus();
				break;

			case 'i': case 'I': 
				player->ManageInventory(SceneOBJs);
				break;

			case 'o': case 'O': UI_GameSettings.Initialize();
				break;

			case '\r': 
			{
				switch (index)
				{
					case 0: 
					{
						system("cls");
						player->DisplayStatus();
						input = _getch();
						break;
					}
						
					
					case 1: 
						break;
					
					case 2: 
						player->ManageInventory(SceneOBJs);
						break;
					
					case 3: 
						UI_GameSettings.Initialize(); 
						break;
					
					case 4: break;
					
					default: break;
				}

				index = 0;
				input = '\0';
				IsPaused = false;
				active = false;
				break;
			}

			default: break;
		}
	}
	else
	{
		switch (input)
		{
			case 27:
			{
				IsPaused = true;
				active = true;
				break;
			}

			case 'c': case 'C': 
				system("cls");
				player->DisplayStatus();
				_getch();
				break;

			case 'i': case 'I': 
				player->ManageInventory(SceneOBJs);
				break;

			case 'o': case 'O': 
				UI_GameSettings.Initialize();
				break;

			if (DebugMode)
			{
				case '\r': 
					_resources_manip = !_resources_manip;
					_exp_manip = !_exp_manip;
					_level_manip = !_level_manip;
					_torch_manip = !_torch_manip;
					player->state = PlayerState::IDLE;
					break;
				
				case '1':
				{
					if (_resources_manip)
					{
						player->cur_health += 1;
						player->cur_mana += 1;
					}
					else
					{
						player->cur_health -= 1;
						player->cur_mana -= 1;

						if (player->cur_health <= 0)
						{
							player->cur_health = 0;
						}

						if (player->cur_mana <= 0)
						{
							player->cur_mana = 0;
						}
					}

					break;
				}

				case '2':
				{
					if (_exp_manip)
					{
						player->cur_experience += 5 * player->level;
						if (player->cur_experience >= player->max_experience)
						{
							player->UpdateStatus(true);
						}
					}
					else
					{
						player->cur_experience = 0;
					}
					break;
				}

				case '3':
				{
					if (_level_manip)
					{
						player->cur_experience = player->max_experience;
						player->UpdateStatus(true);
					}
					else
					{
						player->cur_experience = 0;
						player->SetLevel(1);
					}
					break;
				}

				case '4':
				{
					if (_torch_manip)
					{
						player->torchDuration += 10;
					}
					else
					{
						player->torchDuration -= 10;

						if (player->torchDuration <= 0)
						{
							player->torchDuration = 0;
						}
					}

					break;
				}
			}
			
			
			default:
				return player->Behaviour(input, SceneOBJs);
		}
	}

	return input;
}