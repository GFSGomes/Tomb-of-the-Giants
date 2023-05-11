#include "AbilityCast.hpp";
#include <iomanip>

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
			name = "DOUBLE_STRIKE";
			break;
		case Ability::FIREBALL:
			name = "FIREBALL";
			break;
		case Ability::BRUTAL_STRIKE:
			name = "BRUTAL_STRIKE";
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

enum class Condition {HIT, MISS, CRIT, OFM};

Condition GetCondition(float difficulty, float cost, std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	short hit = rand() % 100 + 1;
	Condition condition = Condition::MISS;

	if (caster->cur_mana >= cost)
	{
		if (caster->accuracy + hit >= difficulty + target->dodge)
		{
			hit + target->critical_chance >= 90 ?
				condition = Condition::CRIT :
				condition = Condition::HIT;
		}
		else
		{
			condition = Condition::MISS;
		}
	}
	else
	{
		condition = Condition::OFM;
	}

	return condition;
}

std::string AbilityCast::Cast(Ability ability, std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	json data = GetAbility(ability);

	std::string name = std::string(data["name"]);
	std::string desc = std::string(data["desc"]);
	float cost		 = data["cost"];
	float multiplier = data["multiplier"];	// Attribute value multiplier i.e.: (120%) Phys. Damage = 1.2;
	float baseValue	 = data["base_value"];	// Defines if the ability has a flat base value
	float difficulty = data["difficulty"];
	float damageDealt = 0;
	std::string log = "";
	std::ostringstream out;
	
	out.precision(2);

	switch (ability)
	{
		default:
			switch (GetCondition(difficulty, cost, caster, target))
			{
				case Condition::CRIT:
				{
					caster->cur_mana -= cost;
					damageDealt = (caster->physical_damage * multiplier * caster->critical_damage) + baseValue;
					out << std::fixed << damageDealt;
					target->cur_health -= damageDealt;
					
					log = caster->name + " used " + name + ":  " + target->name + " HP -" + std::move(out).str() + "[!]";

				} break;
					

				case Condition::HIT:
					caster->cur_mana -= cost;
					damageDealt = (caster->physical_damage * multiplier) + baseValue;
					out << std::fixed << damageDealt;
					target->cur_health -= damageDealt;

					log = caster->name + " used " + name + ":  " + target->name + " HP -" + std::move(out).str();
					break;

				case Condition::MISS:
					caster->cur_mana -= cost;
					log = caster->name + " used " + name + ": " + target->name + " Dodged!";
					break;

				case Condition::OFM:
					log = "";
			}
			break;
	}

	return log;
}