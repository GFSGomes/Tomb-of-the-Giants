#include "MainMenuUI.hpp"
#include "GameSettingsUI.hpp"
#include "SceneManager.hpp"

MainMenuUI mainMenu;

MainMenuUI::MainMenuUI()
{

}

MainMenuUI::~MainMenuUI()
{

}

bool MainMenuUI::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");
		renderer.DisplaySprite(Sprite::TITLE);
		std::cout << "\n";

		switch (index)
		{
			case 0:
			{
				std::cout << " | > Start Game" << "\n";
				std::cout << " |  Settings   " << "\n";
				std::cout << " |  Quit Game  " << "\n";
				break;		   										   
			}

			case 1:			   										   
			{				   										   
				std::cout << " |  Start Game " << "\n";
				std::cout << " | > Settings  " << "\n";
				std::cout << " |  Quit Game  " << "\n";
				break;		   										   
			}

			case 2:			   										   
			{				   										   
				std::cout << " |  Start Game " << "\n";
				std::cout << " |  Settings   " << "\n";
				std::cout << " | > Quit Game " << "\n";
				break;
			}
		}

		input = _getch();

		switch (input)
		{
			case 'w':case 'W':
				if (index > 0) index--;
				break;

			case 's': case 'S':
				if (index < 2) index++;
				break;

			case '\r':
			{
				switch (index)
				{
					case 0:
					{
						GameOver = false;
						SceneManager sceneManager;
						sceneManager.StartGame();
					} break;

					case 1: 
						UI_GameSettings.Initialize(); 
						break;

					case 2: 
						active = false; 
						break;
				}
				
			} break;
		}
	}

	return active;
}