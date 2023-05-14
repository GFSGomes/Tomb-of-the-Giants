#include "InteractionUI.hpp"

InteractionUI UI_Interaction;

InteractionUI::InteractionUI(){}

InteractionUI::~InteractionUI(){}

void InteractionUI::StartCombat(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, bool advantage)
{
	index = 0;
	short barLength = 10;
	short barUnit = 100 / barLength;

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
			std::cout << " -------------------------- GAME OVER --------------------------" << "\n";
			input = _getch();

			active = false;
			GameOver = true;
			return;
		}

		if (enemy->cur_health <= 0)
		{
			system("cls");
			std::cout << " | " << enemy->name << " Lv." << enemy->level << "\n";
			Renderer::StatusBar("HP", enemy->cur_health, enemy->max_health);
			Renderer::DisplaySprite(enemy->sprite);
			short exp = enemy->level + player->level + enemy->level * 15;

			Renderer::Dialog("SUCESS:" + enemy->name + " died!");
			Renderer::Dialog("Exp:" + std::to_string(exp));

			player->cur_experience += exp;
			if (player->cur_experience >= player->max_experience)
			{
				float over = -(player->max_experience - player->cur_experience);
				player->UpdateStatus(true);
				player->cur_experience += over;
			}

			input = _getch();
			enemy->alive = false;
			active = false;
			return;
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
			battleLog = "\0";
			if (battleEffect != "\0")
			{
				_getch();
			}
		}

		if (battleEffect != "\0")
		{
			battleLog = battleEffect;
			battleEffect = "\0";
			StartCombat(player, enemy, advantage);
		}

		std::cout << "\n";
		std::cout << "\n";

		#pragma endregion

		// PLAYER TURN
		if (advantage == true)
		{			
			std::string ability_description = AbilityCast::GetAbility(player->abilities[index])["description"];
			short ability_accuracy = AbilityCast::GetAbility(player->abilities[index])["accuracy"];
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
								std::cout << " | > " << AbilityCast::GetAbilityName(player->abilities[index]) << " (Cost: " << ability_cost << " | Accuracy: " << ability_accuracy << ")" << "\n" :
								std::cout << " |   " << AbilityCast::GetAbilityName(player->abilities[i]) << "\n";
						}
						break;
					}
				}
			}
			std::cout << "\n";

			std::cout << " | " << ability_description << "\n";

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

						battleEffect = player->UpdateSideEffects();
						StartCombat(player, enemy, !advantage);
					}
					break;
				}
			}

			
		}

		// ENEMY TURN
		else
		{
			short randomSkill = rand() % enemy->abilities.size();

			short cost = AbilityCast::GetAbility(enemy->abilities[randomSkill])["cost"];
			
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
				Sleep(500);
			}

			battleEffect = enemy->UpdateSideEffects();
			StartCombat(player, enemy, !advantage);
		}

	}
}

void InteractionUI::InteractionEnemy(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	index = 0;

	while (active)
	{
		system("cls");
		std::cout << " |" << "\n";
		player->isTorchActive ?
			std::cout << " | [?] You spotted an enemy!" << "\n" :
			std::cout << " | [!] You bumped on an enemy!" << "\n";
		std::cout << " |" << "\n";

		std::cout << " | " << enemy->name << " Lv." << enemy->level << "\n";

		Renderer::DisplaySprite(enemy->sprite);

		std::cout << "\n";

		switch (index)
		{
			case 0:
			{
				if (player->isTorchActive)
				{
					std::cout << " | > Attack" << "\n";
					std::cout << " |   Ignore" << "\n";
				} 
				else
				{
					std::cout << " | > Attack  " << "\n";
					std::cout << " |   Try to escape" << "\n";
				}
				break;
			}

			case 1:
			{
				if (player->isTorchActive)
				{
					std::cout << " |   Attack" << "\n";
					std::cout << " | > Ignore" << "\n";
				}
				else
				{
					std::cout << " |   Attack  " << "\n";
					std::cout << " | > Try to escape" << "\n";
				}
				break;
			}
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
			{
				switch (index)
				{
					case 0:
					{
						bool advantage = rand() % 2 + 1; // 0 and 1;
						StartCombat(player, enemy, advantage);
						break;
					} 

					case 1:
					{
						if (player->isTorchActive)
						{
							enemy->Actions(true); // Força o movimento do Inimigo para sair da mesma coordenada que o jogador.
							std::cout << "\n";
							Renderer::Dialog(enemy->name + " didn't noticed you.");
							_getch();
							active = false;
						}
						else
						{
							if (DebugMode)
							{
								enemy->Actions(true);
								active = false;
							}

							short flee = rand() % 100 + 1; // 1 a 100

							if (player->flee + flee >= 50 + enemy->level)
							{
								std::cout << "\n";
								Renderer::Dialog("Luckily, you were ignored.");
								_getch();
								enemy->Actions(true);
								active = false;
							}
							else
							{
								std::cout << "\n";
								Renderer::Dialog("You failed to escape. Starting combat...");
								_getch();
								StartCombat(player, enemy, false);
							}
						}
						break;
					} 

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
		std::cout << " |" << "\n";
		std::cout << " | [!] Item found: " << item->name << "\n";
		std::cout << " |" << "\n";
		Renderer::DisplaySprite(item->sprite);
		std::cout << "\n";

		std::cout << "\n";
		switch(index)
		{
			case 0: 
				std::cout << " | > Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " |   Equip" << "\n" :
				std::cout << " |   Use" << "\n";
				std::cout << " |   Ignore" << "\n";
				break;
				
			case 1: 
				std::cout << " |   Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " | > Equip" << "\n" :
				std::cout << " | > Use" << "\n";
				std::cout << " |   Ignore" << "\n";
				break;

			case 2: 
				std::cout << " |   Add to Inventory" << "\n";
				std::dynamic_pointer_cast<Equipment>(item) ?
				std::cout << " |   Equip" << "\n" :
				std::cout << " |   Use" << "\n";
				std::cout << " | > Ignore" << "\n";
				break;

			default: break;
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W':
			{
				if (index > 0) index--;
				break;
			}

			case 's': case 'S':
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

						Renderer::Dialog(item->name + " added to Inventory.");
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
							player->ChangeEquipment(weapon, true, false);
							return sceneItemRemoval;
						}

						index = 0;
						break;
					}

					case 2:
					{
						sceneItemRemoval = false;
						std::cout << "\n";
						Renderer::Dialog(item->name + " was ignored.");
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
