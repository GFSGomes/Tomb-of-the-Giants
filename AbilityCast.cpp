#include "AbilityCast.hpp";

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
		hit_chance + target->critical_chance >= 90 ?
			condition = Condition::CRIT :
			condition = Condition::HIT;
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
	float brute_value = 0; //
	float apply_value = 0; // Após passar por resistências;

	std::string log = "";
	std::ostringstream out;
	
	out.precision(1);
	#pragma endregion

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
					log += " | Second Hit: ";
				}

				if (caster->accuracy + accuracy >= hit_chance + target->dodge)
				{
					if (hit_chance + target->critical_chance >= 90) {
						brute_value += (caster->physical_damage * multiplier * caster->critical_damage);
						log += " Critical Hit!";
					}
					else
					{
						brute_value += (caster->physical_damage * multiplier);
						log += " Hit!";
					}
				}
				else
				{
					log += " Miss...";
				}
			}

			out << std::fixed << brute_value;

			target->cur_health -= brute_value;

			log += "\n | " + target->name + " -" + std::move(out).str() + " HP.";

			break;
		}

		#pragma region BRUTAL_STRIKE
		case Ability::BRUTAL_STRIKE:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					condition == Condition::CRIT ?
					brute_value = (caster->physical_damage * multiplier * caster->critical_damage) + base_value :
					brute_value = (caster->physical_damage * multiplier) + base_value;

					out << std::fixed << brute_value;

					target->cur_health -= brute_value;
					caster->cur_mana -= cost;
					if (target->cur_health < 0) target->cur_health = 0;
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " -" + std::move(out).str() + " HP.";

					short bleedChance =  rand() % 2 +1; // Range / MIN value;

					if (bleedChance == 1)
					{
						if (target->_bleedind_turns == 0)
						{
							target->_bleedind_turns = 5;
							target->bleed_damage = (caster->physical_damage * 10) / 100;
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
					caster->cur_mana -= cost;
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
		#pragma endregion

		#pragma region Default
		default:
		{
			switch (condition)
			{
				case Condition::HIT: case Condition::CRIT:
				{
					condition == Condition::CRIT ?
						brute_value = (caster->physical_damage * multiplier * caster->critical_damage) + base_value :
						brute_value = (caster->physical_damage * multiplier) + base_value;

					out << std::fixed << brute_value;

					target->cur_health -= brute_value;
					caster->cur_mana -= cost;
					if (target->cur_health < 0) target->cur_health = 0;
					if (caster->cur_mana < 0) caster->cur_mana = 0;

					log = caster->name + ":" + name + ": " + target->name + " HP -" + std::move(out).str();
					break;
				}

				case Condition::MISS:
				{
					caster->cur_mana -= cost;
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
		#pragma endregion
	}

	return log;
}