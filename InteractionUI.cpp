#include "InteractionUI.hpp";

InteractionUI UI_Interaction;

InteractionUI::InteractionUI(){}

InteractionUI::~InteractionUI(){}

void InteractionUI::StartCombat(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, bool advantage)
{
	index = 0;
	short barLength = 10;
	short barUnit = 100 / barLength;

	std::string battleLog = "\n";

	while (active)
	{
		system("cls");
		std::cout << "\n";
		std::cout << battleLog << "\n";

			std::cout << "\n";
			std::cout << "  | " << enemy->name << " - Lv." << enemy->level << "" << "\n";
			std::cout << "  | " << enemy->cur_health << " HP  :";
			for (short i = 0; i < barLength; i++){
				float pct = (enemy->cur_health / enemy->max_health) * 100;
				pct > i * barUnit ?
					std::cout << "=" :
					std::cout << "-" ;
			}
			std::cout << ":" << "\n";

		renderer.DisplaySprite(enemy->sprite);

			// HP
			std::cout << "\n";
			std::cout << "  | " << player->name << " - Lv." << player->level << "" << "\n";

			std::cout << "  | " << player->cur_health << " HP  :";
			for (short i = 0; i < barLength; i++)
			{
				float pct = (player->cur_health / player->max_health) * 100;
				pct > i * barUnit ?
					std::cout << "=" :
					std::cout << "-";
			}
			std::cout << ":" << "\n";

			// MP
			std::cout << "  | " << player->cur_mana << " MP  :";
			for (short i = 0; i < barLength; i++)
			{
				float pct = (player->cur_mana / player->max_mana) * 100;
				pct > i * barUnit ?
					std::cout << "=" :
					std::cout << "-";
			}
			std::cout << ":" << "\n";
		
		std::cout << "\n";

		if (advantage)
		{
			switch (index)
			{
				case 0:
					std::cout << "  [" << AbilityCast::GetAbilityName(player->abilities[0]) << "]" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[1]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[2]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[3]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[4]) << "" << "\n";
					std::cout << "\n";
					std::cout << "   " << AbilityCast::GetAbility(player->abilities[index])["desc"] << "\n";
					break;

				case 1:
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[0]) << "" << "\n";
					std::cout << "  [" << AbilityCast::GetAbilityName(player->abilities[1]) << "]" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[2]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[3]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[4]) << "" << "\n";
					std::cout << "\n";
					std::cout << "   " << AbilityCast::GetAbility(player->abilities[index])["desc"] << "\n";
					break;

				case 2:
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[0]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[1]) << "" << "\n";
					std::cout << "  [" << AbilityCast::GetAbilityName(player->abilities[2]) << "]" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[3]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[4]) << "" << "\n";
					std::cout << "\n";
					std::cout << "   " << AbilityCast::GetAbility(player->abilities[index])["desc"] << "\n";
					break;

				case 3:
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[0]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[1]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[2]) << "" << "\n";
					std::cout << "  [" << AbilityCast::GetAbilityName(player->abilities[3]) << "]" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[4]) << "" << "\n";
					std::cout << "\n";
					std::cout << "   " << AbilityCast::GetAbility(player->abilities[index])["desc"] << "\n";
					break;

				case 4:
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[0]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[1]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[2]) << "" << "\n";
					std::cout << "   " << AbilityCast::GetAbilityName(player->abilities[3]) << "" << "\n";
					std::cout << "  [" << AbilityCast::GetAbilityName(player->abilities[4]) << "]" << "\n";
					std::cout << "\n";
					std::cout << "   " << AbilityCast::GetAbility(player->abilities[index])["desc"] << "\n";
					break;
			}

			input = _getch();

			switch (input)
			{
				case 'w': case 'W':
					if (index > 0) index--;
					break;

				case 's': case 'S':
					if (index < 4) index++;
					break;

				case '1': index = 0; break;
				case '2': index = 1; break;
				case '3': index = 2; break;
				case '4': index = 3; break;
				case '5': index = 4; break;

				case '\r': {
					battleLog = AbilityCast::Cast(player->abilities[index], player, enemy);
					if (battleLog == "")
					{
						battleLog = "  [Insufficient MANA]\n";
					} 
					else
					{
						advantage = !advantage;
					}
				} break;
			}
		}
		else
		{
			short randomSkill = rand() % 4 + 1;
			if (enemy->cur_mana >= AbilityCast::GetAbility(player->abilities[randomSkill])["desc"])
			{
				battleLog = AbilityCast::Cast(enemy->abilities[randomSkill], enemy, player);
			}
			else
			{
				battleLog = AbilityCast::Cast(enemy->abilities[0], enemy, player);
			}

			input = _getch();
			advantage = !advantage;
		}

		if (player->cur_health <= 0)
		{
			player->alive = false;
			system("cls");
			std::cout << "\n";

			renderer.DisplaySprite(Sprite::DEATH);

			std::cout << "" << "\n";
			std::cout << "  [ DEATH ]" << "\n";
			std::cout << "  | " << "\n";
			std::cout << "  | Sorry, little soul..." << "\n";
			std::cout << "  | " << "\n";
			std::cout << "  | Even though you died, I cannot take your soul with me." << "\n";
			std::cout << "  | The tomb of the giants is out of my domains." << "\n";
			std::cout << "  | ..." << "\n";
			input = _getch();
			std::cout << "\n";
			std::cout << "  GAME OVER" << "\n";
			input = _getch();
			active = false;
			GameOver = true;
		}

		if (enemy->cur_health <= 0)
		{
			battleLog = "  [SUCESS: " + enemy->name + " died]" + "\n";
			enemy->alive = false;
			enemy->cur_health = 0;
			input = _getch();
			active = false;
		}
	}
}

void InteractionUI::InteractionEnemy(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	index = 0;

	while (active)
	{
		system("cls");
		std::cout << "\n";
		player->isTorchActive ?
			std::cout << "  [?] You've spotted an enemy [?]" << "\n" :
			std::cout << "  [!] You accidentally bumped on an enemy [!]" << "\n";
		
		std::cout << "  [" << enemy->name << " - Lv." << enemy->level << "]" << "\n";

		renderer.DisplaySprite(enemy->sprite);

		std::cout << "\n";

		switch (index)
		{
			case 0:
				player->isTorchActive ?
				std::cout << "  [Attack]  Ignore" << "\n" :
				std::cout << "  [Attack]  Try to escape" << "\n";
				break;

			case 1:
				player->isTorchActive ?
				std::cout << "   Attack  [Ignore]" << "\n" :
				std::cout << "   Attack  [Try to escape]" << "\n";
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': case 'a': case 'A':
				if (index > 0) index--;
				break;

			case 's': case 'S': case 'd': case 'D':
				if (index < 1) index++;
				break;

			case '\r':
			{
				switch (index)
				{
					case 0:
					{
						bool advantage = rand() % 2 + 0;
						StartCombat(player, enemy, advantage);
					} break;

					case 1:
					{
						if (player->isTorchActive)
						{
							enemy->Actions(true); // Força o movimento do Inimigo para sair da mesma coordenada que o jogador.
							active = false;
						}
						else
						{
							if (DebugMode)
							{
								enemy->Actions(true);
								active = false;
							}

							short flee = rand() % 100 + 1;

							if (player->flee_rate + flee >= 50 + enemy->level)
							{
								enemy->Actions(true);
								active = false;
							}
							else
							{
								std::cout << "\n";
								std::cout << "   You failed to escape. Starting combat..." << "\n";
								input = _getch();
								StartCombat(player, enemy, false);
							}
						}
					} break;

				} break;
			}
		}
	}
}

bool InteractionUI::InteractionItem(std::shared_ptr<Player> player, std::shared_ptr<Item> item)
{
	bool sceneItemRemoval = false;

	while (active)
	{
		system("cls");
		renderer.DisplaySprite(item->sprite);
		std::cout << "  [You found a " << item->name << "]" << "\n";
		std::cout << "\n";
		switch(index)
		{
			case 0: std::cout << "  [Add to Inventory]  Equip   Ignore" << "\n";
				break;
				
			case 1: std::cout << "   Add to Inventory  [Equip]  Ignore" << "\n";
				break;

			case 2: std::cout << "   Add to Inventory   Equip  [Ignore]" << "\n";
				break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': case 'a': case 'A':
				if (index > 0) index--;
				break;

			case 's': case 'S': case 'd': case 'D':
				if (index < 2) index++;
				break;

			case '\r':
			{
				switch (index)
				{
					case 0: 
						player->inventory.AddItem(item, item->stack);
						sceneItemRemoval = true;
						std::cout << "\n";
						std::cout << "  [" << item->name << " added to Inventory]" << "\n";
						break;

					case 1:
						player->inventory.AddItem(item, item->stack);
						sceneItemRemoval = true;
						std::cout << "\n";
						{
							if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
							{
								//potion->Use(player);
							}
							else if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item))
							{
								player->ChangeEquipment(weapon, true);
							}
						}
						break;

					case 2:
						sceneItemRemoval = false;
						std::cout << "\n";
						std::cout << "  [" << item->name << " was ignored]" << "\n";
						break;
				}
				input = _getch();
				active = false;
			}
		}
	}
	return sceneItemRemoval;
}

bool InteractionUI::Initialize()
{
	return false;
}

bool InteractionUI::Initialize(std::shared_ptr<Player> player, std::shared_ptr<GameObject> object)
{
	bool result = false;

	active = true;

	if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(object))
	{
		InteractionEnemy(player, enemy);
	}
	else if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(object))
	{
		result = InteractionItem(player, item);
	}
	
	return result;
}
