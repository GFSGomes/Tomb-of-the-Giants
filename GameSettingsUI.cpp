#include "GameSettingsUI.hpp"
#include "Global.hpp"
#include <conio.h>
#include <iostream>

GameSettingsUI UI_GameSettings;

GameSettingsUI::GameSettingsUI()
{

}

GameSettingsUI::~GameSettingsUI()
{

}

bool GameSettingsUI::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");

		std::cout << " |  GAME SETTINGS            |" << "\n";
		std::cout << " |  -----------------------  |" << "\n";



		switch (index)
		{
			case 0:
			{

				DebugMode ? 
				std::cout << " | > Debug Mode         [X]  |" << "\n" : 
				std::cout << " | > Debug Mode         [ ]  |" << "\n";
				CompatibilityMode ?
				std::cout << " |   Compatibility Mode [X]  |" << "\n" :
				std::cout << " |   Compatibility Mode [ ]  |" << "\n";

				std::cout << " |                           |" << "\n";
				std::cout << " |   Back                    |" << "\n";
				break;
			}

			case 1:
			{
				DebugMode ?
				std::cout << " |   Debug Mode         [X]  |" << "\n" :
				std::cout << " |   Debug Mode         [ ]  |" << "\n";
				CompatibilityMode ?
				std::cout << " | > Compatibility Mode [X]  |" << "\n" :
				std::cout << " | > Compatibility Mode [ ]  |" << "\n";

				std::cout << " |                           |" << "\n";
				std::cout << " |   Back                    |" << "\n";
				break;
			}

			case 2:
			{
				DebugMode ?
				std::cout << " |   Debug Mode         [X]  |" << "\n" :
				std::cout << " |   Debug Mode         [ ]  |" << "\n";
				CompatibilityMode ?
				std::cout << " |   Compatibility Mode [X]  |" << "\n" :
				std::cout << " |   Compatibility Mode [ ]  |" << "\n";

				std::cout << " |                           |" << "\n";
				std::cout << " | > Back                    |" << "\n";
				break;
			}
		}
				std::cout << " '---------------------------'" << "\n";


		input = _getch();

		switch (input)
		{
			case 'w': case 'W':
				if (index > 0) index--; 
				break;

			case 's': case 'S':
				if (index < 2) index++; 
				break;

			case 27: 
				active = false; 
				break;

			case '\r':
			{
				switch (index)
				{
					case 0: 
						DebugMode = !DebugMode;
						index = 2;
						break;

					case 1:
						CompatibilityMode = !CompatibilityMode;
						index = 2;
						break;

					case 2: 
						input = '\0';
						index = 0;
						active = false;
						break;
					
					default: break;
				}
				break;
			}
			default: break;
		}
	}

	return active;
}