#include "GameInterfaceUI.hpp"
#include "GameSettingsUI.hpp"
#include "Global.hpp"
#include <iostream>
#include <conio.h>
#include "Player.hpp"
#include "Renderer.hpp"

GameInterfaceUI UI_GameInterface;
bool IsPaused = false;

GameInterfaceUI::GameInterfaceUI()
{

}

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

void GameInterfaceUI::Input(std::shared_ptr<Player> player, std::vector<std::shared_ptr<GameObject>> SceneOBJ)
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
				player->ManageInventory();
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
						player->ManageInventory();
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
				player->ManageInventory();
				break;

			case 'o': case 'O': 
				UI_GameSettings.Initialize();
				break;

			if (DebugMode)
			{
				case '1':
					player->torchDuration = 999;
					break;

				case '2':
					player->cur_health += 5;
					player->cur_mana += 5;
					break;

				case '3':
					player->cur_health -= 2;
					player->cur_mana -= 2;
					break;

				case '4':
					player->UpdateStatus(true);
					break;
			}
			
			default: player->Actions(input, SceneOBJ);
				break;
		}
	}
}