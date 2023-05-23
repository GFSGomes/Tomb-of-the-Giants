#include "InteractionUI.hpp"
#include "AbilityCast.hpp"
#include "Item.hpp"
#include <Windows.h>
#include <conio.h>
#include "Equipment.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Equipment.hpp"
#include "Renderer.hpp"
#include "Global.hpp"
#include "Miscellaneous.hpp"
#include "Consumable.hpp"
#include "Torch.hpp"

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
			if (player->cur_health <= 0 || enemy->cur_health <= 0)
			{
				_getch();
			}
		}

		if (battleEffect != "\0")
		{
			battleLog = battleEffect;

			battleEffect = "\0";

			if (player->alive && enemy->alive)
			{
				StartCombat(player, enemy, advantage);
			}
		}

		std::cout << "\n";
		std::cout << "\n";
		#pragma endregion

		if (player->cur_health <= 0)
		{
			std::string dialog;
			short count = -1;
			
			system("cls");
			Renderer::DisplaySprite(Sprite::DEATH);
			std::cout << " | DEATH:" << "\n";
			std::cout << "\n";

			while (count < 2)
			{
				count++;

				switch (count)
				{
					case 0: dialog = "How sad..."; break;
					case 1: dialog = "Now, you are one of them, draggin a weapon to and fro."; break;
					case 2: dialog = "There will be no \"rest in peace\" for you."; break;
				}
				
				Renderer::Dialog(dialog, 20);
				std::cout << "\n";

				if (!_getch())
				{
					Sleep(1000);
				}
			}

			player->alive = false;
			GameOver = true;
			active = false;
			return;
		}

		else if (enemy->cur_health <= 0)
		{
			enemy->alive = false;
			system("cls");
			std::cout << " | " << "\n";
			std::cout << " | " << enemy->name << " Lv." << enemy->level << "\n";
			Renderer::StatusBar("HP", enemy->cur_health, enemy->max_health);

			Renderer::DisplaySprite(enemy->sprite);

			short exp = enemy->level + player->level + enemy->level * 15;

			Renderer::Dialog("SUCESS:" + enemy->name + " died!");
			std::cout << "\n\n";
			Renderer::Dialog("Exp:" + std::to_string(exp));

			player->__barrier_turns = 0;
			player->UpdateSideEffects();

			player->cur_experience += exp;

			if (player->cur_experience >= player->max_experience)
			{
				player->UpdateStatus(true);
			}
			_getch();
			active = false;
			return;
		}

		if (advantage)
		{
			if (player->alive)
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

							if (enemy->cur_health <= 0 && player->cur_health <= 0)
							{
								StartCombat(player, enemy, !advantage);
							}
						}
						break;
					}
				}
			}
		}
		else
		{
			if (enemy->alive)
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

				_getch();

				battleEffect = enemy->UpdateSideEffects();

				if (enemy->cur_health <= 0 && player->cur_health <= 0)
				{
					StartCombat(player, enemy, !advantage);
				}
			}
		}
	}
}
void InteractionUI::InteractionEnemy(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, std::vector<std::shared_ptr<GameObject>> SceneOBJs)
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
						bool advantage = rand() % 2; // 0 and 1;
						StartCombat(player, enemy, advantage);
						if (enemy->cur_health <= 0)
						{
							enemy->SpawnRandom();
						}
						active = false;
						break;
					}

					case 1:
					{
						if (player->isTorchActive)
						{
							enemy->Behaviour(true, SceneOBJs); // Força o movimento do Inimigo para sair da mesma coordenada que o jogador.

							std::cout << "\n";

							Renderer::Dialog(enemy->name + " didn't noticed you.");

							_getch();

							active = false;
						}
						else
						{
							if (DebugMode)
							{
								enemy->Behaviour(true, SceneOBJs);
								return;
							}

							short flee = rand() % 101;

							if (player->flee + flee >= 50 + enemy->level)
							{
								std::cout << "\n";
								Renderer::Dialog("Sucess.");

								_getch();

								enemy->Behaviour(true, SceneOBJs);

								return;
							}
							else
							{
								std::cout << "\n";

								Renderer::Dialog("You failed to escape. Starting combat...");

								_getch();

								StartCombat(player, enemy, false);

								if (!enemy->alive)
								{
									enemy->SpawnRandom();
								}

								active = false;
								return;
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
				if (std::dynamic_pointer_cast<Equipment>(item)){std::cout << " |   Equip" << "\n";}
				else if (std::dynamic_pointer_cast<Consumable>(item)){std::cout << " |   Use" << "\n";}
				std::cout << " |   Ignore" << "\n";
				break;
				
			case 1: 
				std::cout << " |   Add to Inventory" << "\n";
				
				if (std::dynamic_pointer_cast<Equipment>(item)){std::cout << " | > Equip" << "\n";}
				else if (std::dynamic_pointer_cast<Consumable>(item)){std::cout << " | > Use" << "\n";}
				
				if (std::dynamic_pointer_cast<Miscellaneous>(item)){std::cout << " | > Ignore" << "\n";}
				else {std::cout << " |   Ignore" << "\n";}
				
				break;

			if (!std::dynamic_pointer_cast<Miscellaneous>(item))
			{
				case 2:
					std::cout << " |   Add to Inventory" << "\n";
					std::dynamic_pointer_cast<Equipment>(item) ?
					std::cout << " |   Equip" << "\n" :
					std::cout << " |   Use" << "\n";
					std::cout << " | > Ignore" << "\n";
					break;
			}
			

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
				if (std::dynamic_pointer_cast<Miscellaneous>(item))
				{
					if (index < 1) index++;
				}
				else
				{
					if (index < 2) index++;
				}
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
							break;
						}
						else if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
						{
							player->inventory.AddItem(equip, 1);
							player->ChangeEquipment(equip);
							break;
						}
						else if (std::shared_ptr<Torch> torch = std::dynamic_pointer_cast<Torch>(item))
						{
							short value = rand() % 30 + 10;
							player->torchDuration += value;
							Renderer::Dialog("Torch +" + value);
							break;
						}
						else
						{
							sceneItemRemoval = false;
							std::cout << "\n";
							Renderer::Dialog(item->name + " was ignored.");
							break;
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
bool InteractionUI::Initialize(std::shared_ptr<Player> player, std::shared_ptr<GameObject> object, std::vector<std::shared_ptr<GameObject>> SceneOBJs)
{
	bool result = false;

	active = true;

	if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(object))
	{
		InteractionEnemy(player, enemy, SceneOBJs);
	}
	else if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(object))
	{
		result = InteractionItem(player, item);
	}
	
	return result;
}
