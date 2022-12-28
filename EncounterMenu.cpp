#include "EncounterMenu.hpp"

EncounterMenu encounterMenu;

EncounterMenu::EncounterMenu()
{

}

EncounterMenu::~EncounterMenu()
{

}

void EncounterMenu::Battle(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	std::string log_0;
	std::string log_1;
	bool swap;

	while (active)
	{
		system("cls");
		std::cout << "   BATTLE LOG" << "\n";
		
		std::cout << "   > " << log_0 << "\n";
		std::cout << "   > " << log_1 << "\n";

		std::cout << "\n";
		std::cout << "   " << enemy->name << "\n";

		std::cout << "   ";

		for (int i = 0; i < enemy->cur_health; i++)
			std::cout << "=";
		for (int i = 0; i < (enemy->cur_health - enemy->max_health); i++)
			std::cout << "-";

		std::cout << "\n";

		renderer.DisplaySprite(enemy->sprite);

		std::cout << "\n";

		std::cout << "   What do you want to do?" << "\n\n";

		switch (index)
		{
			case 0:
				std::cout << "   > Attack" << "\n";
				std::cout << "     Run" << "\n";
				break;

			case 1:
				std::cout << "     Attack" << "\n";
				std::cout << "   > Run" << "\n";
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': 
				if (index > 0) 
					index--; 
				break;

			case 's': case 'S':
				if (index < 1) 
					index++; 
				break;

			case '\r':
			{
				switch (index)
				{
					case 0: 
						// Skill 1
						// log_0 = player->...attackX
						// Abilidade deve retornar uma descrição
						break;

					case 1:
						// Skill 2
						break;

					//...
				}

			} break;

			default: break;
		}
	}
}

void EncounterMenu::Initialize(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	active = true;

	while (active)
	{
		system("cls");
		std::cout << "   You bumped into an enemy" << "\n";
		std::cout << "   " << enemy->name << "\n";

		std::cout << "   ";
		for (int i = 0; i < enemy->cur_health; i++)
			std::cout << "=";
		for (int i = 0; i < (enemy->cur_health - enemy->max_health); i++)
			std::cout << "-";

		std::cout << "\n";
		renderer.DisplaySprite(enemy->sprite);
		std::cout << "\n";

		std::cout << "   What do you want to do?" << "\n\n";

		switch (index)
		{
			case 0:
				std::cout << "   > Start Battle!" << "\n";
				std::cout << "     Run!" << "\n";
				break;

			case 1:
				std::cout << "     Start Battle!" << "\n";
				std::cout << "   > Run!" << "\n";
				break;

			default: break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': 
				if (index > 0) 
					index--; 
				break;
			
			case 's': case 'S':
				if (index < 1) 
					index++;
				break;
			
			case '\r':
			{
				switch (index)
				{
					case 0:
						index = 0;
						input = '\0';
						active = true;
						Battle(player, enemy);
						break;

					case 1:
						//if sucess:
						break;
				}
				
			} break;

			default: break;
		}
	}
}