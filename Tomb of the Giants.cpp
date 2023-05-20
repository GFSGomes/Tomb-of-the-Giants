#include "MainMenuUI.hpp"
#include <iostream>
#include <iomanip>
#include "Renderer.hpp"
//#include <windows.h>
//#include <conio.h>

int main()
{
	std::cout << std::fixed << std::setprecision(1);
	std::ios::sync_with_stdio(false);
	mainMenu.Initialize();
	return 0;

	/*while (true)
	{
		if (_kbhit())
		{
			break;
		}
		//short g = rand() % 5;		// Saída: 0, 1, 2, 3, 4
		//short g = rand() % 5 + 1;	// Saída: 1, 2, 3, 4, 5
		//short g = rand() % 6;		// Saída: 0, 1, 2, 3, 4, 5
		short g = rand() % (6+1);	// Saída: 0, 1, 2, 3, 4, 5, 6
		Sleep(100);
		std::cout << g << " ";
	}

	return 0;*/
}