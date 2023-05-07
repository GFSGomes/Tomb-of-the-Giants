#include "GameInterface.hpp"
#include "Settings.hpp"

GameInterface GUI_Controls;

GameInterface::GameInterface()
{

}

GameInterface::~GameInterface()
{

}

void GameInterface::Initialize(){}
void GameInterface::Initialize(std::shared_ptr<Player> player)
{
	system("cls");

	active ?
		DebugMode ?
		std::cout << "   |Esc| Close - DebugMode" << "\n" :
		std::cout << "   |Esc| Close  " << "\n" :
		DebugMode ?
		std::cout << "   |Esc| Menu - DebugMode" << "\n" :
		std::cout << "   |Esc| Menu  " << "\n";

	if (active)
	{
		switch (index)
		{
			case 0:
			{
				std::cout << "   > Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}					 
			break;				 
								 
			case 1:				 
			{					 
				std::cout << "     Character  " << "\n";
				std::cout << "   > Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}					 
			break;				 
								 
			case 2:				 
			{					 
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "   > Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}					 
			break;				 
								 
			case 3:				 
			{					 
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "   > Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}					 
			break;				 
								 
			case 4:				 
			{					 
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "   > Leave Game" << "\n";
			}
			break;
		}
	}
	std::cout << "\n";

	std::cout << "   " << player->name <<" (Lvl. " << player->level << ")" << "\n";
	std::cout << "   HP  <";

	short bar_size = 20;
	short part = 100 / bar_size;

	for (short i = 0; i < bar_size; i++)
	{
		float pct = ((player->cur_health / player->max_health) * 100);
		
		if (pct > i * part)
		{
			std::cout << "=";
		}
		else
		{
			std::cout << "-";
		}
	}
	std::cout << ">" << "\n";


	std::cout << "   MP  <";
	for (short i = 0; i < bar_size; i++) // 20 = Comprimento da Barra
	{
		float pct = ((player->cur_mana / player->max_mana) * 100);
		if (pct > i * part)
		{
			std::cout << "=";
		}
		else
		{
			std::cout << "-";
		}
	}
	std::cout << ">" << "\n";

	
	std::cout << "   Exp <";
	for (short i = 0; i < bar_size; i++) // 20 = Comprimento da Barra
	{
		float pct = ((player->cur_experience / player->max_experience) * 100);
		if (pct > i * part)
		{
			std::cout << "_";
		}
		else
		{
			std::cout << " ";
		}
	}
	std::cout << ">" << "\n";
}

void GameInterface::Input(std::shared_ptr<Player> player)
{
	std::cout << "\n";
	std::cout << "\n";

	if (player->isTorchActive)
	{
		std::cout << "     |W|   To       |T| Torch [X] " << player->torchDuration << "\n";
		std::cout << "   |A|S|D| Move" << "\n";
	}
	else
	{
		std::cout << "     |W|   To       |T| Torch [ ] " << player->torchDuration << "\n";
		std::cout << "   |A|S|D| Move" << "\n";
	}

	std::cout << "\n";

	if (DebugMode)
	{
		std::cout << "   |1| Torch +10" << "\n";
		std::cout << "   |2| Health++, Mana++" << "\n";
		std::cout << "   |3| Health--, Mana--" << "\n";
		std::cout << "   |4| Level++" << "\n";
	}

	input = _getch();

	if (active)
	{
		switch (input)
		{
			case 27: active = false; break;
			case 'w': case 'W': 
				if (index > 0) index--;
				break;
			case 's': case 'S':
				if (index < 4) index++;
				break;

			case '\r': 
				switch (index)
				{
					case 0: 
						system("cls");
						player->DisplayStatus();
						_getch(); 
						break;
					
					case 1: break;
					
					case 2: player->inventory.Initialize(); break;
					
					case 3: settings.Initialize(); break;
					
					case 4: break;
					
					default: break;
				}

				index = 0;
				input = '\0';
				active = false;
				break;
			
			default:
				break;
		}
	}
	else
	{
		switch (input)
		{
			case 27: active = true; break;
			case '1': player->torchDuration += 10; break;
			case '2': player->cur_health++; player->cur_mana++; break;
			case '3': player->cur_health--; player->cur_mana--; break;
			case '4': player->UpdateStatus(true); break;
			default:
				player->Actions(input);
				break;
		}
	}
}