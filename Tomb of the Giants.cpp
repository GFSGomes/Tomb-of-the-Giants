#include "MainMenuUI.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	std::cout << std::fixed << std::setprecision(1);
	std::ios::sync_with_stdio(false);
	srand(time(0));
	mainMenu.Initialize();
	return 0;

	/*while (true)
	{
		if (_kbhit())
		{
			break;
		}
		short g = rand() % 4 + 0; // Range / MIN value;
		Sleep(100);
		std::cout << g << " ";
	}

	return 0;*/
}