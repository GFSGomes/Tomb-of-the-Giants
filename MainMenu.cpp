#include "MainMenu.hpp"
#include "Settings.hpp"
#include "SceneManager.hpp"

MainMenu mainMenu;

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");

		renderer.DisplaySprite(Sprite::TITLE);

		switch (index)
		{
			case 0:
			{
				std::cout << "     > Start Game" << "\n";
				std::cout << "       Settings" << "\n";
				std::cout << "       Quit Game" << "\n";
				break;		     
			}

			case 1:			     
			{				     
				std::cout << "       Start Game" << "\n";
				std::cout << "     > Settings" << "\n";
				std::cout << "       Quit Game" << "\n";
				break;		     
			}

			case 2:			     
			{				     
				std::cout << "       Start Game" << "\n";
				std::cout << "       Settings" << "\n";
				std::cout << "     > Quit Game" << "\n";
				break;
			}

			default: 
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w':case 'W':
			{
				if (index > 0)
				{
					index--;
				}

				break;
			} 

			case 's': case 'S':
			{
				if (index < 2)
				{
					index++;
				}

				break;
			} 

			case '\r':
			{
				switch (index)
				{
					case 0: 
					{
						GameOver = false;
						SceneManager sceneManager;
						sceneManager.StartGame();
						 break;
					}

					case 1: 
						settings.Initialize(); 
						break;

					case 2: 
						active = false; 
						break;

					default: 
						break;
				}

				break;
			} 

			default: 
				break;
		}
	}
}