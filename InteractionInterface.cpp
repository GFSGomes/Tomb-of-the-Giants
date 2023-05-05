#include "InteractionInterface.hpp"
#include <iomanip>
#include <cctype>

InteractionInterface GUI_Interaction;

InteractionInterface::InteractionInterface(){}

InteractionInterface::~InteractionInterface(){}

void InteractionInterface::StartCombat(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	short bar_size = 30;
	short part = 100 / bar_size;

	std::string log_0 = "\n";
	std::string log_1 = "\n";
	bool swap;

	while (active)
	{
		if (player->cur_health <= 0)
		{
			index = 0;
			system("cls");
			std::cout << "\n";
			std::cout << "   So, looks like you died, as I warned you." << "\n";
			std::cout << "   Now your corpse will wander forever in the darkness" << "\n";
			std::cout << "   seeking for any spark of light." << "\n";
			input = _getch();
			GameOver = true;
			active = false;
			return;
		}

		if (enemy->cur_health <= 0)
		{
			index = 0;
			system("cls");
			std::cout << "\n";
			std::cout << "   " << enemy->name << " is DEAD!" << "\n";
			input = _getch();
			active = false;
			return;
		}

		system("cls");
		std::cout << "\n";
		std::cout << "   > " << log_0;
		std::cout << "   > " << log_1;

		// Enemy Info
		std::cout << "\n";
		std::cout << "   " << enemy->name << " [" << enemy->level << "]" << "\n";
		std::cout << "   HP ";
		for (short i = 0; i < bar_size; i++)
		{
			float pct = ((enemy->cur_health / enemy->max_health) * 100);
			/*if (pct > i * part) std::cout << "■";
			else std::cout << "□";*/
			if (pct > i * part) std::cout << "=";
			else std::cout << "-";
		}
		std::cout << " | " << enemy->cur_health << "/" << enemy->max_health << "\n";

		renderer.DisplaySprite(enemy->sprite);
		renderer.DisplaySprite(Sprite::ICON_TARGET);

		// PLAYER
		std::cout << "\n";
		std::cout << "   " << player->name << " [" << player->level << "]" << "\n";
		std::cout << "   HP ";
		for (short i = 0; i < bar_size; i++)
		{
			float pct = ((player->cur_health / player->max_health) * 100);
			/*if (pct > i * part) std::cout << "■";
			else std::cout << "□";*/
			if (pct > i * part) std::cout << "=";
			else std::cout << "-";
		}
		std::cout << " | " << player->cur_health << "/" << player->max_health << "\n";
		std::cout << "   MP ";
		for (short i = 0; i < bar_size; i++)
		{
			float pct = ((player->cur_mana / player->max_mana) * 100);
			/*if (pct > i * part) std::cout << "▬";
			else std::cout << "═";*/
			if (pct > i * part) std::cout << "=";
			else std::cout << "-";
		}
		std::cout << " | " << player->cur_mana << "/" << player->max_mana << "" << "\n";

		std::cout << "   What do you want to do?" << "\n\n";

		switch (index)
		{
			case 0:
				std::cout << "   [ATTACK]" << "\n";
				std::cout << "    SKILL 1" << "\n";
				std::cout << "    SKILL 2" << "\n";
				std::cout << "    SKILL 3" << "\n";
				std::cout << "    SKILL 4" << "\n";
				std::cout << "    RUN" << "\n";
				break;
			case 1:
				std::cout << "    ATTACK" << "\n";
				std::cout << "   [SKILL 1]" << "\n";
				std::cout << "    SKILL 2" << "\n";
				std::cout << "    SKILL 3" << "\n";
				std::cout << "    SKILL 4" << "\n";
				std::cout << "    RUN" << "\n";
				break;
			case 2:
				std::cout << "    ATTACK" << "\n";
				std::cout << "    SKILL 1" << "\n";
				std::cout << "   [SKILL 2]" << "\n";
				std::cout << "    SKILL 3" << "\n";
				std::cout << "    SKILL 4" << "\n";
				std::cout << "    RUN" << "\n";
				break;
			case 3:
				std::cout << "    ATTACK" << "\n";
				std::cout << "    SKILL 1" << "\n";
				std::cout << "    SKILL 2" << "\n";
				std::cout << "   [SKILL 3]" << "\n";
				std::cout << "    SKILL 4" << "\n";
				std::cout << "    RUN" << "\n";
				break;
			case 4:
				std::cout << "    ATTACK" << "\n";
				std::cout << "    SKILL 1" << "\n";
				std::cout << "    SKILL 2" << "\n";
				std::cout << "    SKILL 3" << "\n";
				std::cout << "   [SKILL 4]" << "\n";
				std::cout << "    RUN" << "\n";
				break;
			case 5:
				std::cout << "    ATTACK" << "\n";
				std::cout << "    SKILL 1" << "\n";
				std::cout << "    SKILL 2" << "\n";
				std::cout << "    SKILL 3" << "\n";
				std::cout << "    SKILL 4" << "\n";
				std::cout << "   [RUN]" << "\n";
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': 
				if (index > 0) index--; 
				break;

			case 's': case 'S':
				if (index < 5) index++;
				break;

			case '1': index = 0;
				break;
			case '2': index = 1;
				break; 
			case '3': index = 2;
				break; 
			case '4': index = 3;
				 break;
			case '5': index = 4;
				 break;
			case '6': index = 5;
				 break;

			case '\r': {
				switch (index) // ABILITYCASTING
				{
					case 0:
						log_0 = AbilityCast::Cast(player->abilities[0], player, enemy) + "\n";
						log_1 = AbilityCast::Cast(enemy->abilities[0], enemy, player);
						break;

					case 1:

						break;
					
					case 2:
						break;

					case 3:
						break;
					
					case 4:
						break;

					case 5:
						index = 0;
						active = false;
						return;
				}
				
			} break;
			
			default: 
				break;
		}
	}
}

void InteractionInterface::Initialize(){}
void InteractionInterface::Initialize(std::shared_ptr<Player> player, std::shared_ptr<GameObject> obj)
{
	active = true;

	if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
	{
		short bar_width = 15;
		short bar_chunk = 100 / bar_width;
		
		while (active)
		{
			system("cls");
			std::cout << std::setprecision(4);

			std::cout << "\n";
			player->isTorchActive ?
				std::cout << "   You bumped into an enemy!" << "\n" :
				std::cout << "   You accidentaly bumped into an enemy!" << "\n";
			std::cout << "   " << enemy->name << " [Lv." << enemy->level << "]" << "\n";

			renderer.DisplaySprite(enemy->sprite);
			
			std::cout << "\n";
			std::cout << "   > What do you want to do?" << "\n";

			switch (index)
			{
				case 0:
						std::cout << "   [Attack]" << "\n";
					player->isTorchActive ?
						std::cout << "    Ignore" << "\n" :
						std::cout << "    Run" << "\n";
					break;
				case 1:
						std::cout << "    Attack" << "\n";
					player->isTorchActive ?
						std::cout << "   [Ignore]" << "\n" :
						std::cout << "   [Run]" << "\n";
					break;
			}

			input = _getch();

			switch (input)
			{
				case 'w': case 'W':
					if (index > 0) index--;
					break;
				case 's': case 'S':
					if (index < 1) index++;
					break;
				case '\r':
					switch (index)
					{
						case 0: 
							StartCombat(player, enemy);
							break;
						case 1: 
							active = false; // Temporary
							break;
					}
					break;
			}
		}
	}

	else if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(obj))
	{
		while (active)
		{
			std::cout << "\n";
			std::cout << "   You found a " << item->name << "!" << "\n";
			std::cout << "   It was sent to your inventory." << "\n";
			std::cout << "   > Press any key to proceed." << "\n";
			input = _getch();
			active = false;
		}
	}
}