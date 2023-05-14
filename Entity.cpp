#include "Entity.hpp"

Entity::Entity() :
	level{0}, cur_experience{0}, max_experience{50}, status_points{0},
	STR{0}, CON{0}, INT{0}, AGI{0}, DEX{0},
	cur_health{0}, max_health{0}, 
	cur_mana{0}, max_mana{0},
	physical_damage{0}, physical_resistance{0},
	magical_damage{0}, magical_resistance{0},
	accuracy{0}, dodge{0},
	flee{0},
	critical_chance{0}, critical_damage{0},
	_bleedind_turns{0}, bleed_damage{0},
	_poisoned_turns{0}, poison_damage{0},
	_burning_turns{0},  burning_damage{0},
	_stunned_turns {0}, can_fight{true},
	__barrier_turns{0}, barrier_value{0}, _store_cur_health{0},
	alive{true}
{
	UpdateStatus(true);

	// TEMPORARIO:
	abilities.push_back(Ability::NONE);
	abilities.push_back(Ability::ATTACK);

	inventory.AddItem(std::make_shared<Weapon>(WeaponType::SWORD, "Necrowolf Blade", "The developer personal weapon.", 76, 76, 76, 0, 0), 1);
	inventory.AddItem(std::make_shared<Weapon>(WeaponType::SWORD, "Training Sword", "A blunt sword used for training.", 3, 0, 0, 0, 0), 1);
	inventory.AddItem(std::make_shared<Potion>(PotionType::MINOR_HEALTH_POTION), 2);

	inventory.AddItem(std::make_shared<Armor>(ArmorType::BODY, Sprite::HEAVY_BODY, "STEEL PLATE", "", 4, 1, -10, -5, 0, 0, 0, 0, 0), 1);
	inventory.AddItem(std::make_shared<Armor>(ArmorType::BODY, Sprite::MEDIUM_BODY, "GIBBON", "", 2, 1, 5, -2, 0, 0, 0, 0, 0), 1);
	inventory.AddItem(std::make_shared<Armor>(ArmorType::BODY, Sprite::LIGHT_BODY, "MAGE ROBE", "", 1, 3, 7, 2, 0, 0, 4, 0, 0), 1);
}

Entity::~Entity(){}

void Entity::Actions(){}

std::string Entity::UpdateSideEffects()
{
	std::string log = "\0";
	std::ostringstream out;
	out.precision(1);

	if (_bleedind_turns > 0)
	{
		cur_health -= bleed_damage;
		_bleedind_turns--;
		out << std::fixed << bleed_damage;

		log += name + " suffered from Bleeding -" + std::move(out).str() + " HP.\n";
	}

	if (_poisoned_turns > 0)
	{
		cur_health -= poison_damage;
		_poisoned_turns--;
		out << std::fixed << poison_damage;

		log += name + " suffered from Poison -" + std::move(out).str() + " HP.\n";
	}

	if (_burning_turns > 0)
	{
		cur_health -= burning_damage;

		_burning_turns--;

		out << std::fixed << burning_damage;

		log += name + " suffered from Burning -" + std::move(out).str() + " HP.\n";
	}

	if (_stunned_turns > 0)
	{
		can_fight = false;
		_stunned_turns--;
	}

	if (__barrier_turns > 0)
	{
		__barrier_turns--;
	}


	if (_stunned_turns == 0)
	{
		can_fight = true;
	}

	if (_bleedind_turns == 0)
	{
		bleed_damage = 0;
	}

	if (_burning_turns == 0)
	{
		burning_damage = 0;
	}

	if (_poisoned_turns == 0)
	{
		poison_damage = 0;
	}

	if (cur_health <= _store_cur_health)
	{
		// Barrier was broken
		log += name + "'s MANA SHIELD has been destroyed.";
	}
	else if (__barrier_turns == 0 && _store_cur_health != 0)
	{
		// Barrier fades
		float extra_health;
		extra_health = cur_health - _store_cur_health;
		cur_health -= extra_health;
		log += name + "'s MANA SHIELD fades.";
	}

	if (cur_health < 0)
	{
		cur_health = 0;
	}
	if (cur_mana < 0)
	{
		cur_mana = 0;
	}
	return log;
}
void Entity::ApplyEquipedItemStats()
{
	for (short i = 0; i < inventory.Container.size(); i++)
	{
		if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(inventory.Container[i].item))
		{
			if (equip->equiped)
			{
				if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(equip))
				{
					physical_damage += weapon->physical_power;
					magical_damage += weapon->magical_power;
					accuracy += weapon->accuracy;
					critical_chance += weapon->critical_chance;
					critical_damage += weapon->critical_damage;
				}

				if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(equip))
				{
					physical_resistance += armor->physical_resistance;
					magical_resistance += armor->magical_resistance;
					dodge += armor->dodge;
					flee += armor->flee;
					STR += armor->bonusSTR;
					CON += armor->bonusCON;
					INT += armor->bonusINT;
					AGI += armor->bonusAGI;
					DEX += armor->bonusDEX;
				}
			}
		}
	}
}
/// <summary>
/// 
/// </summary>
/// <param name="_equip"></param>
/// <param name="_shouldBeEquiped"></param>
/// <param name="_beingDiscarded"></param>
void Entity::ChangeEquipment(std::shared_ptr<Equipment> _equip, bool _shouldBeEquiped = true, bool _beingDiscarded = false)
{
	for (short i = 0; i < inventory.Container.size(); i++)
	{
		if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(inventory.Container[i].item))
		{
			if (equip->equiped)
			{
				if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(equip))
				{
					if (std::dynamic_pointer_cast<Weapon>(_equip))
					{
						physical_damage -= weapon->physical_power;
						magical_damage -= weapon->magical_power;
						accuracy -= weapon->accuracy;
						critical_chance -= weapon->critical_chance;
						critical_damage -= weapon->critical_damage;
						weapon->equiped = false;
					}
				}
				else if (std::shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(equip))
				{
					if (std::dynamic_pointer_cast<Armor>(_equip))
					{
						if (std::dynamic_pointer_cast<Armor>(equip)->armorType == armor->armorType)
						{
							physical_resistance -= armor->physical_resistance;
							magical_resistance -= armor->magical_resistance;
							dodge -= armor->dodge;
							flee -= armor->flee;
							STR -= armor->bonusSTR;
							CON -= armor->bonusCON;
							INT -= armor->bonusINT;
							AGI -= armor->bonusAGI;
							DEX -= armor->bonusDEX;
							armor->equiped = false;
						}
					}
				}
			}
		}
	}

	std::cout << "\n";
	if (_shouldBeEquiped == true) {
		Renderer::Dialog(_equip->name + " has been equiped.");
		if (_getch()){}
	}
	else 
	{
		if (!_beingDiscarded)
		{
			Renderer::Dialog(_equip->name + " has been unequiped.");
			if (_getch()){}
		}
	}
	// <-- Unequip

	// Equip received item -->
	_equip->equiped = _shouldBeEquiped;

	ApplyEquipedItemStats();
}

void Entity::DrinkPotion(std::shared_ptr<Potion> _potion)
{
	// Impedindo aplicar valores e descarte se VIDA/MANA estiver cheia:
	std::cout << "\n";
	switch (_potion->potionType)
	{
		case PotionType::MINOR_HEALTH_POTION: case PotionType::MEDIUM_HEALTH_POTION: case PotionType::GREATER_HEALTH_POTION:
		{
			if (cur_health == max_health)
			{
				Renderer::Dialog("Health is full. " + _potion->name + " will remain in your Inventory.");
				if (_getch()){}
				return;
			}
			break;
		}
		case PotionType::MINOR_MANA_POTION: case PotionType::MEDIUM_MANA_POTION: case PotionType::GREATER_MANA_POTION:
		{
			if (cur_mana == max_mana)
			{
				Renderer::Dialog("Mana is full. " + _potion->name + " will remain in your Inventory.");
				if (_getch()){}
				return;
			}
			break;
		}
	}

	// Limitando curas à VIDA/MANA máxima:
	if (_potion->health_recovery > max_health - cur_health)
	{
		_potion->health_recovery = max_health - cur_health;
	}
	if (_potion->mana_recovery > max_mana - cur_mana)
	{
		_potion->mana_recovery = max_mana - cur_mana;
	}

	// Aplicando valores:
	cur_health += _potion->health_recovery;
	cur_mana += _potion->mana_recovery;

	// Render:
	if (_potion->health_recovery > 0)
	{
		Renderer::Dialog("+" + std::to_string(_potion->health_recovery) + " Health Points has been restored.");
	}

	if (_potion->mana_recovery > 0)
	{
		Renderer::Dialog("+" + std::to_string(_potion->mana_recovery) + " Mana Points has been restored.");
	}

	inventory.DiscardItem(_potion, 1, true);

	if (_getch()){}
}

void Entity::ManageInventory()
{
	short index = 0;
	char input = '\0';
	bool active = true;

	std::shared_ptr<Item> item = inventory.Initialize();
	
	while (active)
	{
		if (!item)
		{
			active = false;
			return;
		}

		system("cls");
		std::cout << "\n";
		std::cout << " | " << item->name << "\n";
		Renderer::DisplaySprite(item->sprite);
		std::cout << "\n";

		std::cout << " | [?] Description: " << "\n";
		std::cout << " | " << item->description << "\n";
		std::cout << " | " << "\n";
		if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item))
		{
			if (weapon->physical_power != 0) std::cout << " | " << weapon->physical_power << " Physical Power" << "\n";
			if (weapon->magical_power != 0) std::cout << " | " << weapon->magical_power << " Magical Power" << "\n";
			if (weapon->accuracy != 0) std::cout << " | " << weapon->accuracy << " Accuracy" << "\n";
			if (weapon->critical_chance != 0) std::cout << " | " << weapon->critical_chance << " Critical Chance" << "\n";
			if (weapon->critical_damage != 0) std::cout << " | " << weapon->critical_damage << " Critical Damage" << "\n";
		}
		std::cout << "\n";

		switch (index)
		{
			case 0:
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
				{
					equip->equiped ?
						std::cout << " | > Unequip" << "\n" :
						std::cout << " | > Equip " << "\n";
				}
				else {
					std::cout << " | > Use " << item->name << "\n";
				}
				std::cout << " |   Discard" << "\n";
					
				break;
			}
			case 1:
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
				{
					equip->equiped ?
						std::cout << " |   Unequip" << "\n" :
						std::cout << " |   Equip " << "\n";
				}
				else
				{
					std::cout << " |   Use " << item->name << "\n";
				}
				std::cout << " | > Discard" << "\n";
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
						if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
						{
							if (equip->equiped)
							{
								ChangeEquipment(equip, false, false);
							}
							else
							{
								ChangeEquipment(equip, true, false);
							}
						}

						if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
						{
							DrinkPotion(potion);
						}

						ManageInventory();
						active = false;
						break;
						break;
					}

					case 1:
					{
						active = false;
						if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
						{
							if (equip->equiped)
							{
								ChangeEquipment(equip, false, true);
							}
							inventory.DiscardItem(item, 1, false);
						}
						else
						{
							inventory.DiscardItem(item, 0, false);
						}

						break;
					}
				}
			} 

			case 27:
			{
				item = nullptr;
				active = false;
				ManageInventory();
				break;
			}
		}
	}
}

void Entity::DisplayStatus()
{
	std::cout << " | " << name << " (" << level << ")" << "\n";
	Renderer::StatusBar("HP", cur_health, max_health);
	Renderer::StatusBar("MP", cur_mana, max_mana);
	Renderer::StatusBar("XP", cur_experience, max_experience);
	std::cout << " | --------------------------" << "\n";
	std::cout << " | (" << cur_health     << "/" << max_health << ") Health" << "\n";
	std::cout << " | (" << cur_mana       << "/" << max_mana << ") Mana" << "\n";
	std::cout << " | (" << cur_experience << "/" << max_experience << ") Experience" << "\n";
	std::cout << " | +" << status_points  << " Free Status Points" << "\n";
	std::cout << " | --------------------------" << "\n";
	
	std::cout << " | " << STR << " STR" << "\n";
	std::cout << " | " << CON << " CON" << "\n";
	std::cout << " | " << INT << " INT" << "\n";
	std::cout << " | " << AGI << " AGI" << "\n";
	std::cout << " | " << DEX << " DEX" << "\n";
	std::cout << " | --------------------------"   <<"\n";

	std::cout << " | " << physical_damage     << " Physical Damage    " << "\n";
	std::cout << " | " << magical_damage      << " Magical Damage     " << "\n";
	std::cout << " | " << physical_resistance << " Physical Resistance" << "\n";
	std::cout << " | " << magical_resistance  << " Magical Resistance " << "\n";
	std::cout << " | --------------------------"   << "\n";

	std::cout << " | " << critical_chance << " Critical Chance" << "\n";
	std::cout << " | " << critical_damage << " Critical Damage" << "\n";
	std::cout << " | --------------------------" << "\n";

	std::cout << " | " << dodge    << " Dodge    " << "\n";
	std::cout << " | " << accuracy << " Accuracy " << "\n";
	std::cout << " | " << flee	    << " Flee     " << "\n";
}

void Entity::UpdateStatus(bool level_up = false)
{	
	/*
	| Health    | Mana      | P.Dmg     | M.Dmg     |
	| STR x 0.5 | INT x 1.5 | STR x 0.7 | INT x 0.8 |
	| CON x 1.0 | 5         | DEX x 0.1 | Weapon    |
	| 5         |           | Weapon    |           |
							   
	| P.Res     | M.Res     | Dodge     | Accuracy  |
	| CON x 0.5 | CON x 0.1 | AGI x 2.0 | DEX x 1.5 |
	| AGI x 0.2 | INT x 0.3 |           |           |
	|           | AGI x 0.1 |           |           |
	
	| C. Chance | C. Damage | Flee      |
	| DEX x 1.0 | DEX x 1.0 | AGI x 1.0 |
	| AGI x 0.5 |           |           |
	|           |           |           |
	*/
	max_health = 5 + (CON * 1.0) + (STR * 0.5);
	max_mana   = 5 + (INT * 1.5);

	physical_damage = (STR * 0.7) + (DEX * 0.1);
	magical_damage  = (INT * 0.8);

	physical_resistance = (CON * 0.5) + (AGI * 0.2);
	magical_resistance  = (INT * 0.5) + (CON * 0.1) + (AGI * 0.1);

	dodge = (AGI * 2);
	accuracy = (DEX * 1.5);
	
	critical_damage = (DEX);
	critical_chance = (DEX) + (AGI * 0.5);
	
	flee = (AGI);

	if (cur_health > max_health)
	{
		cur_health = max_health;
	}

	if (cur_mana > max_mana)
	{
		cur_mana = max_mana;
	}

	if (level_up)
	{
		level++;
		cur_experience = 0;
		max_experience *= 1.15;
		status_points++;

		STR++; CON++; INT++; AGI++; DEX++;
		UpdateStatus(false);
		cur_health	= max_health;
		cur_mana	= max_mana;
	}

	ApplyEquipedItemStats();
}