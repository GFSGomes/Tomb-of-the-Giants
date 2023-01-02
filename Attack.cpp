#include "Attack.hpp"

Attack::Attack()
{
	cost = 0;
	baseBonus = 0;
	bonusMultiplier = 1;
	requiredAccuracy = 15;

	name = "ATTACK";
	description = R"(
	ATTACK
	A basic attack using (100%) Physical Damage.

	Damage: 100%
	Difficulty: 15)";
}

Attack::~Attack()
{

}

std::string Attack::Cast(std::shared_ptr<Entity> caster, std::shared_ptr<Entity> target)
{
	short hit = rand() % 100 + 1;

	if (caster->accuracy + hit >= requiredAccuracy + target->dodge)
	{
		if (hit + target->critical_chance >= 90)
		{
			target->cur_health -= caster->physical_damage * caster->critical_damage;
			return caster->name + " used " + name + ": CRITICAL HIT! " + target->name + " lost " + std::to_string(caster->physical_damage * caster->critical_damage) + "!";
		}

		target->cur_health -= caster->physical_damage;
		return caster->name + " used " + name + ": " + target->name + " lost " + std::to_string(caster->physical_damage) + ".";
	}
	else
	{
		return caster->name + " used " + name + ": " + target->name + " DODGED!";
	}
}