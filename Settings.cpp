#include "Settings.hpp"

Settings settings;

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");

		std::cout << "\n";

		std::cout			  << "   Settings" << "\n\n";
		switch (index)
		{
			case 0:
			{
				DebugMode ? 
					std::cout << "  > Debug Mode [X]" << "\n" : 
					std::cout << "  > Debug Mode [ ]" << "\n";
					std::cout << "     Back" << "\n";
				break;
			}
			case 1:
			{
				DebugMode ?
					std::cout << "     Debug Mode [X]" << "\n" :
					std::cout << "     Debug Mode [ ]" << "\n";
					std::cout << "  > Back" << "\n";
				break;
			}
			default: break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': if (index > 0) index--; break;
			case 's': case 'S': if (index < 1) index++; break;
			case 27: active = false; break;
			case '\r':
			{
				switch (index)
				{
					case 0: DebugMode = !DebugMode; break;
					case 1: 
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
}