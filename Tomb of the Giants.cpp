#include "MainMenuUI.hpp"

int main()
{
	std::cout << std::fixed << std::setprecision(1);
	std::ios::sync_with_stdio(false);
	srand(time(0));
	mainMenu.Initialize();
	return 0;
}