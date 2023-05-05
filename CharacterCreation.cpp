#include "CharacterCreation.hpp"

CharacterCreation::CharacterCreation()
{

}

CharacterCreation::~CharacterCreation()
{

}

void CharacterCreation::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");
		std::cout << "\n";
		std::cout << "   Enter your name:";

		std::string name;
		std::cin >> name;

		std::cout << "   Select your class:";
		switch (index)
		{
			case 0: 
				std::cout << "   [Warrior]" << "\n";
				std::cout << "    Archer" << "\n";
				std::cout << "    Mage" << "\n";
				std::cout << "    Rogue" << "\n";
				break;
			case 1: 
				std::cout << "    Warrior" << "\n";
				std::cout << "   [Archer]" << "\n";
				std::cout << "    Mage" << "\n";
				std::cout << "    Rogue" << "\n";
				break;
			case 2: 
				std::cout << "    Warrior" << "\n";
				std::cout << "    Archer" << "\n";
				std::cout << "   [Mage]" << "\n";
				std::cout << "    Rogue" << "\n";
				break;
			case 3: 
				std::cout << "    Warrior" << "\n";
				std::cout << "    Archer" << "\n";
				std::cout << "    Mage" << "\n";
				std::cout << "   [Rogue]" << "\n";
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': 
				if (index > 0) index--;
				break;
			case 's': case 'S':
				if (index < 3) index++;
				break;
			case '\r':
				switch (index)
				{
					case 0: break;
					case 1: break;
					case 2: break;
					case 3: break;
				}
				break;
		}
	}
}