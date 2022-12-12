#include "EncounterMenu.hpp"

EncounterMenu::EncounterMenu()
{

}

EncounterMenu::~EncounterMenu()
{

}

void EncounterMenu::Battle(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	
	if (!player->active || !enemy->active)
	{
		active = false;
		return;
	}

	system("cls");
	std::cout << "   --- In combat with " << enemy->name << " ---" << "\n";
	enemy->renderer.DisplaySprite();
	std::cout << "   What do you want to do?" << "\n";

	switch (index)
	{
		default:

			// Abilities
			
			break;
	}
}

void EncounterMenu::Initialize(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	system("cls");
	std::cout << "   --- You bumped into a " << enemy->name << " ---" << "\n";
	enemy->renderer.DisplaySprite();
	std::cout << "   What do you want to do?" << "\n";

	switch (index)
	{
		case 0:
			std::cout << "  > Attack!" << "\n";
			std::cout << "     Run!" << "\n";
			break;

		case 1:
			std::cout << "     Attack!" << "\n";
			std::cout << "  > Run!" << "\n";
			break;

		default: break;
	}

	input = _getch();

	switch (input)
	{
		case 'w': case 'W': if (index > 0) index--; break;
		case 's': case 'S':if (index < 1) index++; break;
		case '\r':
		{
			switch (index)
			{
				case 0:
				{
					index = 0;
					input = '\0';
					active = true;

					while (active)
					{
						Battle(player, enemy);
					}

				} break;

				case 1:
				{
					// Haverá teste de sucesso na fuga
					enemy->Actions(true);
				}
				break;
			}
		} break;

		default: break;
	}
}