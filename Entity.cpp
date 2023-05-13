#include "Entity.hpp"

Entity::Entity() :
	level{0}, cur_experience{0}, max_experience{0}, status_points{0},
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
	_stunned_turns {0}, can_fight{true},
	alive{true}
{
	max_experience = 50;
	UpdateStatus(true);

	// TEMPORARIO:
	abilities.push_back(Ability::ATTACK);
	abilities.push_back(Ability::NONE);
	abilities.push_back(Ability::DOUBLE_STRIKE);
	abilities.push_back(Ability::BRUTAL_STRIKE);

	inventory.AddItem(std::make_shared<Weapon>(WeaponType::SWORD, "Necrowolf Blade", "The developer personal weapon.", 76, 0), 1);
	inventory.AddItem(std::make_shared<Weapon>(WeaponType::SWORD, "Training Sword", "A blunt sword used for training.", 3, 0), 1);
	inventory.AddItem(std::make_shared<Potion>(PotionType::MINOR_HEALTH_POTION), 2);
}

Entity::~Entity(){}

void Entity::Actions(){}

std::string Entity::UpdateSideEffects()
{
	std::string log;
	std::ostringstream out;
	out.precision(1);

	if (_bleedind_turns > 0)
	{
		cur_health -= bleed_damage;
		_bleedind_turns--;
		out << std::fixed << bleed_damage;

		log += "\n" + name + " suffered from Bleeding -" + std::move(out).str() + " HP.";
	}

	if (_poisoned_turns > 0)
	{
		cur_health -= poison_damage;
		_poisoned_turns--;
		out << std::fixed << poison_damage;

		log += "\n" + name + " suffered from Poison -" + std::move(out).str() + " HP.";
	}

	if (_stunned_turns > 0)
	{
		if (_stunned_turns == 0)
		{
			can_fight = true;
		}
		else
		{
			can_fight = false;
			_stunned_turns--;
		}
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
					physical_damage += weapon->b_might;
					magical_damage += weapon->b_magic;
				}
			}
		}
	}
}

void Entity::ChangeEquipment(std::shared_ptr<Equipment> _equip, bool _shouldBeEquiped = true)
{
	for (short i = 0; i < inventory.Container.size(); i++)
	{
		if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(inventory.Container[i].item))
		{
			if (equip->equiped)
			{
				if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(equip))
				{
					physical_damage -= weapon->b_might;
					magical_damage -= weapon->b_magic;
					weapon->equiped = false;
				}
			}
		}
	}

	// Precisa estar em escopo, eu acho.
	if (_shouldBeEquiped == true) {
		Renderer::Dialog(_equip->name + " has been equiped.");
	}
	else {
		Renderer::Dialog(_equip->name + " has been unequiped.");
	}

	_equip->equiped = _shouldBeEquiped;

	ApplyEquipedItemStats();

	_getch();
}

void Entity::DrinkPotion(std::shared_ptr<Potion> _potion)
{
	// Impedindo aplicar valores e descarte se VIDA/MANA estiver cheia:
	switch (_potion->potionType)
	{
		case PotionType::MINOR_HEALTH_POTION: case PotionType::MEDIUM_HEALTH_POTION: case PotionType::GREATER_HEALTH_POTION:
		{
			if (cur_health == max_health)
			{
				Renderer::Dialog("Health is full. " + _potion->name + " will remain in your Inventory.");
				_getch();
				return;
			}
			break;
		}
		case PotionType::MINOR_MANA_POTION: case PotionType::MEDIUM_MANA_POTION: case PotionType::GREATER_MANA_POTION:
		{
			if (cur_mana == max_mana)
			{
				Renderer::Dialog("Mana is full. " + _potion->name + " will remain in your Inventory.");
				_getch();
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

	inventory.DiscardItem(_potion, 1);

	_getch();
}

void Entity::ManageInventory()
{
	bool active = false;
	short index = 0;
	char input = '\0';

	active = true;

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

		Renderer::DisplaySprite(item->sprite);
		std::cout << "\n";

		std::cout << " | " << item->name << "\n";
		std::cout << "\n";

		if (std::shared_ptr<Equipment> equipment = std::dynamic_pointer_cast<Equipment>(item))
		{
			!equipment->equiped ?
				std::cout << " | [Equip " << equipment->name << "]" << "\n" :
				std::cout << " | [Unequip]" << "\n";
		}
		else if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
		{
			std::cout << " [Drink]" << "\n";
		}

		std::cout << "\n";
		std::cout << " | " << item->description << "\n";

		if (std::shared_ptr<Weapon> weap = std::dynamic_pointer_cast<Weapon>(item))
		{
			if (weap->b_might != 0)
			std::cout << " | Bonus STR: +" << weap->b_might << "\n";
			
			if (weap->b_magic != 0)
			std::cout << " | Bonus INT: +" << weap->b_magic << "\n";
		}
		else if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
		{
			if (potion->health_recovery != 0)
			std::cout << " | Bonus Health: +" << potion->health_recovery << "\n";
			
			if (potion->mana_recovery != 0)
			std::cout << " | Bonus Health: +" << potion->mana_recovery << "\n";
		}

		input = _getch();

		switch (input)
		{
			case '\r':
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(item))
				{
					if (equip->equiped)
					{
						ChangeEquipment(equip, false);
					}
					else
					{
						ChangeEquipment(equip, true);
					}

				}

				if (std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(item))
				{
					DrinkPotion(potion);
				}

				ManageInventory();
				active = false;
				break;
			} 

			case 27:
				active = false;
				break;

			default: 
				break;
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
	| STR x 1.5 | INT x 1.5 | STR x 0.3 | INT x 0.5 |
	| CON x 2.0 | 10        | DEX x 0.1 | Weapon    |
	| 10        |           | Weapon    |           |
							   
	| P.Res     | M.Res     | Dodge     | Accuracy  |
	| CON x 0.5 | CON x 0.1 | AGI x 2.0 | DEX x 1.5 |
	| AGI x 0.2 | INT x 0.3 |           |           |
	|           | AGI x 0.1 |           |           |
	
	| C. Chance | C. Damage | Flee      |
	| DEX x 1.0 | DEX x 1.0 | AGI x 1.0 |
	| AGI x 0.5 |           |           |
	|           |           |           |
	*/
	max_health = 10 + (CON * 2.0) + (STR * 0.5);
	max_mana   = 10 + (INT * 1.5);

	physical_damage = (STR * 0.3) + (DEX * 0.1);
	magical_damage  = (INT * 0.5);

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