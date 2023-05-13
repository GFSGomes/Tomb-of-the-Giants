#include "InteractionUI.hpp";

InteractionUI UI_Interaction;

InteractionUI::InteractionUI(){}

InteractionUI::~InteractionUI(){}

void InteractionUI::StartCombat(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, bool advantage)
{
	index = 0;
	short barLength = 10;
	short barUnit = 100 / barLength;

	std::string battleLog = "\0";

	while (active)
	{
		#pragma region BattleResults
		if (player->cur_health <= 0)
		{
			player->alive = false;
			system("cls");
			Renderer::DisplaySprite(Sprite::DEATH);
			input = _getch();

			std::cout << "\n";
			std::cout << "-------------------------- GAME OVER --------------------------" << "\n";
			input = _getch();

			active = false;
			GameOver = true;
			return;
		}

		if (enemy->cur_health <= 0)
		{
			system("cls");
			Renderer::StatusBar("HP", enemy->cur_health, enemy->max_health);
			Renderer::DisplaySprite(enemy->sprite);
			short exp = enemy->level + player->level + enemy->level * 15;

			Renderer::Dialog("SUCESS:" + enemy->name + " died!");
			Renderer::Dialog("Exp:" + std::to_string(exp));

			player->cur_experience += exp;
			if (player->cur_experience >= player->max_experience)
			{
				float over = player->max_experience - player->cur_experience;
				player->UpdateStatus(true);
				player->cur_experience += over;
			}

			input = _getch();
			enemy->alive = false;
			active = false;
		}
		#pragma endregion
		
		#pragma region Rendering
		system("cls");

		std::cout << " | " << enemy->name << " Lv." << enemy->level << "\n";
		Renderer::StatusBar("HP", enemy->cur_health, enemy->max_health);
		Renderer::StatusBar("MP", enemy->cur_mana, enemy->max_mana);

		Renderer::DisplaySprite(enemy->sprite);
		std::cout << "\n";

		std::cout << " | " << player->name << " Lv." << player->level << "\n";
		Renderer::StatusBar("HP", player->cur_health, player->max_health);
		Renderer::StatusBar("MP", player->cur_mana, player->max_mana);
		std::cout << "\n";

		if (battleLog != "\0")
		{
			Renderer::Dialog(battleLog);

			if (advantage)
			{
				if (player->UpdateSideEffects() != "")
				{
					battleLog = player->UpdateSideEffects();
					Renderer::Dialog(battleLog);
					_getch();
				}
				std::cout << "\n";
			}
			else
			{
				if (enemy->UpdateSideEffects() != "")
				{
					battleLog = enemy->UpdateSideEffects();
					Renderer::Dialog(battleLog);
					_getch();
				}
				std::cout << "\n";
			}
			std::cout << "\n";
		}
		else
		{
			std::cout << "\n";
			std::cout << "\n";
			std::cout << "\n";
		}

		battleLog = "\0";
		#pragma endregion

		// PLAYER TURN
		if (advantage)
		{
			if (!player->can_fight)
			{
				battleLog = player->name + " is stunned for " + std::to_string(player->_stunned_turns) + "turns";
				advantage = !advantage;
				return;
			}
			
			std::string abilityDescription = AbilityCast::GetAbility(player->abilities[index])["description"];
			
			switch (index)
			{
				if (player->abilities.size() >= index)
				{
					case 0: case 1: case 2: case 3: case 4:
					{
						for (short i = 0; i < player->abilities.size(); i++)
						{
							short ability_cost = AbilityCast::GetAbility(player->abilities[i])["cost"];

							i == index ?
								std::cout << " [" << AbilityCast::GetAbilityName(player->abilities[index]) << " (" << ability_cost << ")" << "]" << "\n" :
								std::cout << "  " << AbilityCast::GetAbilityName(player->abilities[i]) << " (" << ability_cost << ")" << "\n";
						}
						break;
					}
				}
			}
			std::cout << "\n";

			std::cout << " | " << abilityDescription << "\n";

			input = _getch();

			switch (input)
			{
				case 'w': case 'W':
					if (index > 0) index--;
					break;

				case 's': case 'S':
					if (index < player->abilities.size() - 1) index++;
					break;

				case '\r': 
				{
					battleLog = AbilityCast::Cast(player->abilities[index], player, enemy);

					if (battleLog == "")
					{
						battleLog = "[!] WARING: Insufficient Mana [!]\n";
					}
					else
					{
						advantage = !advantage;
					}
					break;
				}
			}
		}

		// ENEMY TURN
		else
		{
			if (!enemy->can_fight){
				battleLog = enemy->name + " is stunned for " + std::to_string(enemy->_stunned_turns) + "turns";
				advantage = !advantage;
				return;
			}

			short randomSkill = rand() % enemy->abilities.size();

			short cost = AbilityCast::GetAbility(player->abilities[randomSkill])["cost"];
			
			if (enemy->cur_mana >= cost)
			{
				battleLog = AbilityCast::Cast(enemy->abilities[randomSkill], enemy, player);
			}
			else
			{
				battleLog = AbilityCast::Cast(enemy->abilities[0], enemy, player);
			}

			if (!_getch())
			{
				Sleep(10000);
			}
			advantage = !advantage;
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

		Renderer::DisplaySprite(enemy->sprite);

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
							enemy->Actions(true); // For�a o movimento do Inimigo para sair da mesma coordenada que o jogador.
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

							if (player->flee + flee >= 50 + enemy->level)
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
		Renderer::DisplaySprite(item->sprite);
		std::cout << "\n";

		std::cout << " | You found a " << item->name << "\n";
		std::cout << "\n";
		switch(index)
		{
			case 0: 
				std::cout << " | > Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " |  Equip" << "\n" :
				std::cout << " |  Use" << "\n";
				std::cout << " |  Ignore" << "\n";
				break;
				
			case 1: 
				std::cout << " |  Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " | > Equip" << "\n" :
				std::cout << " | > Use" << "\n";
				std::cout << " |  Ignore" << "\n";
				break;

			case 2: 
				std::cout << " |  Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " |  Equip" << "\n" :
				std::cout << " |  Use" << "\n";
				std::cout << " | > Ignore" << "\n";
				break;

			default: break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W': case 'a': case 'A':
			{
				if (index > 0) index--;
				break;
			}

			case 's': case 'S': case 'd': case 'D':
			{
				if (index < 2) index++;
				break;
			}

			case '\r':
			{
				switch (index)
				{
					case 0: 
					{
						player->inventory.AddItem(item, 1);

						sceneItemRemoval = true;

						std::cout << "\n";

						Renderer::Dialog(item->name + " added to Inventory");
						break;
					}

					case 1:
					{
						sceneItemRemoval = true;

						std::cout << "\n";

						if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
						{
							player->DrinkPotion(potion);
							return sceneItemRemoval;
						}
						else if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item))
						{
							player->inventory.AddItem(weapon, 1);
							player->ChangeEquipment(weapon, true);
							return sceneItemRemoval;
						}

						index = 0;
						break;
					}

					case 2:
					{
						sceneItemRemoval = false;
						std::cout << "\n";
						Renderer::Dialog(item->name + " was ignored and desappeared into the darkness.");
						break;
					}
						
				}

				input = _getch();
				active = false;
			}


			case 27:
			{
				index = 0;
				break;
			}

			default:
			{
				break;
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
