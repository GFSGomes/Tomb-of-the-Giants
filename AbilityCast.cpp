#include "AbilityCast.hpp"
#include "Entity.hpp"
#include <sstream>
#include <fstream>
#include <windows.h>

AbilityCast::~AbilityCast()
{

}

std::string AbilityCast::GetAbilityName(Ability ability)
{
	std::string name = "";

	switch (ability)
	{
		case Ability::NONE:
			name = "NONE";
			break;
		case Ability::ATTACK: 
			name = "ATTACK";
			break;
		case Ability::DOUBLE_STRIKE: 
			name = "DOUBLE STRIKE";
			break;
		case Ability::BRUTAL_STRIKE:
			name = "BRUTAL STRIKE";
			break;
		case Ability::FIREBALL:
			name = "FIREBALL";
			break;
		case Ability::MANA_SHIELD:
			name = "MANA SHIELD";
			break;
	}

	return name;
}

json AbilityCast::GetAbility(Ability ability)
{
	std::ifstream file("database.json");

	json data = json::parse(file); // Objeto JSON

	json abilities = data["abilities"]; // Array Abilities contendo objetos

	json abilityData;

	for (short i = 0; i < abilities.size(); i++)
	{
		if (abilities[i].find("name").value() == GetAbilityName(ability))
		{
			abilityData = abilities[i];
		}
	}

	return abilityData;
}

Condition GetCondition(float _accuracy, float _cost, std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	std::srand(time(0));
	short hit_chance = rand() % 100 + 1;
	Condition condition;

	if (caster->accuracy + _accuracy >= hit_chance + target->dodge)
	{
		if ((caster->critical_chance - 100) / (hit_chance + 100) <= 0.505)
		{
			condition = Condition::CRIT;
		}
		else
		{
			condition = Condition::HIT;
		}
	}
	else
	{
		condition = Condition::MISS;
	}

	return condition;
}

std::string AbilityCast::Cast(Ability ability, std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	#pragma region GettingAbility
	json data = GetAbility(ability);
	std::string name = std::string(data["name"]);
	std::string desc = std::string(data["description"]);
	float cost		 = data["cost"];
	float multiplier = data["multiplier"];	// Attribute value multiplier i.e.: (120%) Phys.Damage = 1.2;
	float base_value = data["base_value"];	// Defines if the ability has a flat base value
	short accuracy = data["accuracy"];
	
	Condition condition;
	float raw_value = 0; // Dano bruto, antes de passar pelas resistências;
	float applyed_value = 0; // Após passar por resistências;

	std::string log = "";
	std::ostringstream out;
	
	out.precision(2);
	#pragma endregion

	// REDUÇÃO NA MANA DO CASTER:
	if (caster->cur_mana >= cost)
	{
		caster->cur_mana -= cost;

		if (caster->cur_mana < 0)
		{
			caster->cur_mana = 0;
		}

		condition = GetCondition(accuracy, cost, caster, target);
	}
	else
	{
		return "";
	}

	switch (ability)
	{
		case Ability::ATTACK:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					condition == Condition::CRIT ?
						raw_value = (caster->physical_damage * multiplier * caster->critical_damage) + base_value :
						raw_value = (caster->physical_damage * multiplier) + base_value;

					applyed_value = ((raw_value * 100) + caster->level) / (100 + target->physical_resistance + target->level);

					out << std::fixed << applyed_value;

					target->cur_health -= applyed_value;

					log = caster->name + ":" + name + ":\n | " + target->name + " -" + std::move(out).str() + " HP.";
					break;
				}

				case Condition::MISS:
				{
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " dodged!";
					break;
				}

				case Condition::OFM:
				{
					log = "";
					break;
				}
			}

			break;
		}

		case Ability::DOUBLE_STRIKE:
		{
			short hit_chance;

			for (short i = 0; i < 2; i++)
			{
				hit_chance = rand() % 100 + 1;

				if (i == 0)
				{
					log = caster->name + ":" + name + ": " + "\n | First Hit: ";
				}
				if (i == 1)
				{
					Sleep(10);
					log += "\n | Second Hit: ";
				}

				if (caster->accuracy + accuracy >= hit_chance + target->dodge)
				{
					if ((caster->critical_chance - 100) / (hit_chance + 100) <= 0.505) {
						raw_value += (caster->physical_damage * multiplier * caster->critical_damage);
						log += " CRITICAL!";
					}
					else
					{
						raw_value += (caster->physical_damage * multiplier);
						log += " HIT!";
					}
				}
				else
				{
					log += " Miss";
				}
			}

			applyed_value = ((raw_value * 100) + caster->level) / (100 + target->physical_resistance + target->level);

			out << std::fixed << applyed_value;

			target->cur_health -= applyed_value;

			log += "\n | " + target->name + " -" + std::move(out).str() + " HP.";

			break;
		}

		case Ability::BRUTAL_STRIKE:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					condition == Condition::CRIT ?
					raw_value = (caster->physical_damage * multiplier * caster->critical_damage) + base_value :
					raw_value = (caster->physical_damage * multiplier) + base_value;

					applyed_value = ((raw_value * 100) + caster->level) / (100 + target->physical_resistance + target->level);

					out << std::fixed << applyed_value;

					target->cur_health -= applyed_value;

					log = caster->name + ":" + name + ":\n | " + target->name + " -" + std::move(out).str() + " HP.";

					short bleedChance =  rand() % 2 + 1; // Está 100!

					if (bleedChance == 1)
					{
						if (target->_bleedind_turns == 0)
						{
							target->_bleedind_turns = 5;
							target->bleed_damage = (caster->physical_damage * 30) / 100;
							log += "\n | " + target->name + " is now BLEEDING.";
						}
						else
						{
							log += "\n | [!] " + target->name + " is already BLEEDING.";
						}
					}

					break;
				}

				case Condition::MISS:
				{
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " dodged!";
					break;
				}

				case Condition::OFM:
				{
					log = "";
					break;
				}
			}

			break;
		}

		case Ability::FIREBALL:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					raw_value = (caster->magical_damage * multiplier) + base_value;

					applyed_value = ((raw_value * 100) + caster->level) / (100 + target->magical_resistance + target->level);


					out << std::fixed << applyed_value;

					target->cur_health -= applyed_value;

					log = caster->name + ":" + name + ": " + target->name + " -" + std::move(out).str() + " HP.";

					// Set Burning:
					if (target->_burning_turns == 0)
					{
						target->_burning_turns = 3;
						target->burning_damage = (caster->magical_damage * 50) / 100;
						log += "\n | " + target->name + " is now BURNING.";
					}
					else
					{
						log += "\n | [!] " + target->name + " is already BURNING.";
					}

					break;
				}

				case Condition::MISS:
				{
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " dodged!";
					break;
				}

				case Condition::OFM:
				{
					log = "";
					break;
				}
			}
			break;
		}

		case Ability::MANA_SHIELD:
		{
			raw_value = base_value + (caster->magical_damage * multiplier);

			caster->barrier_value = raw_value;

			if (caster->__barrier_turns == 0)
			{
				caster->_store_cur_health = caster->cur_health;

				caster->cur_health += caster->barrier_value;

				log = caster->name + ":" + name + ":\n " + caster->name + " was surrounded by a barrier.";
			}
			else
			{
				log = caster->name + ":" + name + ":\n " + caster->name + " barrier duration renewed.";
			}

			caster->__barrier_turns = 4;
			
			break;
		}

		default:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					condition == Condition::CRIT ?
						raw_value = (caster->physical_damage * multiplier * caster->critical_damage) + base_value :
						raw_value = (caster->physical_damage * multiplier) + base_value;

					applyed_value = ((raw_value * 100) + caster->level) / (100 + target->physical_resistance + target->level);

					out << std::fixed << applyed_value;

					target->cur_health -= applyed_value;

					log = caster->name + ":" + name + ":\n | " + target->name + " -" + std::move(out).str() + " HP.";
					break;
				}

				case Condition::MISS:
				{
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " dodged!";
					break;
				}

				case Condition::OFM:
				{
					log = "";
					break;
				}
			}

			break;
		}
	}

	if (target->cur_health < 0)
	{
		target->cur_health = 0;
	}

	return log;
}