#include "GameMenu.hpp"
#include "Settings.hpp"

GameMenu gameMenu;

GameMenu::GameMenu()
{

}

GameMenu::~GameMenu()
{

}

void GameMenu::Initialize()
{
	system("cls");

	std::cout << "\n";

	active ?
		DebugMode ? 
			std::cout << "   [Esc] Close - DebugMode" << "\n" : 
			std::cout << "   [Esc] Close  " << "\n" :
		DebugMode ? 
			std::cout << "   [Esc] Menu - DebugMode" << "\n" : 
			std::cout << "   [Esc] Menu  " << "\n";

	std::cout << "\n";


	if (active)
	{
		switch (index)
		{
			case 0:
			{
				std::cout << "  > Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}				    
			break;			    
							    
			case 1:			    
			{				    
				std::cout << "     Character  " << "\n";
				std::cout << "  > Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}				    
			break;			    
							    
			case 2:			    
			{				    
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "  > Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}				    
			break;			    
							    
			case 3:			    
			{				    
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "  > Settings" << "\n";
				std::cout << "     Leave Game" << "\n";
			}				    
			break;			    
							    
			case 4:			    
			{				    
				std::cout << "     Character" << "\n";
				std::cout << "     Abilities" << "\n";
				std::cout << "     Inventory" << "\n";
				std::cout << "     Settings" << "\n";
				std::cout << "  > Leave Game" << "\n";
			}
			break;
		}
		std::cout << "\n";
	}
}

void GameMenu::Input(std::shared_ptr<Player> player)
{
	std::cout << "\n";

	if (player->isTorchActive)
	{
		std::cout << "     [W]   To       [T] Torch ((X) " << player->torchDuration << ")" << "\n";
		std::cout << "   [A|S|D] Move     Your torch is lit." << "\n";
	}
	else
	{
		std::cout << "     [W]   To       [T] Torch (( ) " << player->torchDuration << ")" << "\n";
		std::cout << "   [A|S|D] Move" << "\n";
	}

	if (DebugMode)
	{
		std::cout << "\n";
		std::cout << "   DevTools\n";
		std::cout << "   [1] Torch +10\n";
		std::cout << "   [2] Health +1\n";
	}

	input = _getch();

	switch (input)
	{
		case 27: active = !active; break;
		
		case 'w': case 'W':
		{
			if (active)
			{
				if (index > 0)
					index--;
			}
			else
			{
				player->Actions(input);
			}
				
		} 
		break;

		case 's': case 'S':
		{
			if (active)
			{
				if (index < 4) 
					index++;
			}
			else
			{
				player->Actions(input);
			}
				
		} break;


		case '1':
		{
			if (DebugMode)
			{
				player->torchDuration += 10;
			}

		} break;
		
		case '2':
		{
			if (DebugMode)
			{
				player->cur_health++;
			}

		} break;

		case '\r':
		{
			switch (index)
			{
				case 0: break;
				case 1: break;
				case 2: player->inventory.Initialize();  break;
				case 3: settings.Initialize(); break;
				case 4: break;

				default: return;
			}

			input = '\0';
			index = 0;
			active = false;
		}

		default: player->Actions(input); break;
	}
}