#include "AbilityCast.hpp";

AbilityCast::~AbilityCast()
{

}

std::string AbilityCast::GetAbilityName(Ability ability)
{
	std::string name = "";

	switch (ability)
	{
		case Ability::ATTACK: 
			name = "ATTACK"; 
			break;
		case Ability::DOUBLE_STRIKE: 
			name = "DOUBLE STRIKE";  
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

std::string AbilityCast::Cast(Ability ability, std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	enum class Condition {HIT, MISS, CRIT};

	Condition condition = Condition::MISS;

	json data = GetAbility(ability);

	std::string name = std::string(data["name"]);
	std::string desc = std::string(data["desc"]);
	float cost		 = data["cost"];
	float multiplier = data["multiplier"];	// Attribute value multiplier i.e.: (120%) Phys. Damage = 1.2;
	float baseValue	 = data["base_value"];	// Defines if the ability has a flat base value
	float difficulty = data["difficulty"];

	std::string log = "";

	short hit = rand() % 100 + 1;

	if (caster->accuracy + hit >= difficulty + target->dodge){
		hit + target->critical_chance >= 90 ?
		condition = Condition::CRIT	:
		condition = Condition::HIT;
	}
	else {
		condition = Condition::MISS;
	}
	

	switch (ability)
	{
		case Ability::ATTACK:
			switch (condition)
			{
				case Condition::CRIT:
					target->cur_health -= (caster->physical_damage * multiplier * caster->critical_damage) + baseValue;
					log = "CRITICAL HIT! " + target->name + " lost " + std::to_string(caster->physical_damage * caster->critical_damage) + "HP!";
					break;

				case Condition::HIT:
					target->cur_health -= caster->physical_damage * multiplier + baseValue;
					log = target->name + " lost " + std::to_string(caster->physical_damage) + "HP.";
					break;

				case Condition::MISS:
					log = target->name + " DODGED!";
					break;
			}
			break;
	}

	return log;
}