#include "DoubleStrike.hpp"

DoubleStrike::DoubleStrike()
{
	name = "Double Strike";
	description = "Attacks the target two times with dealing 70% of Physical Damage for each hit. Each strike has chance to be a critical hit.";
	cost = 8; // mana;
	requiredAccuracy = 30;
}
DoubleStrike::~DoubleStrike(){}

std::string DoubleStrike::Use(Entity* _attacker, Entity* _target)
{
	short sucess = rand() % 100;

	bool crit_0 = false;
	bool crit_1 = false;

	std::string message;

	if (_attacker->cur_mana >= cost)
	{
		_attacker->cur_mana -= cost;

		if (sucess >= requiredAccuracy + _target->dodge_rate)
		{
			if (sucess >= 100 - _attacker->critical_rate)
			{
				crit_0 = true;
			}
			if (sucess >= 100 - _attacker->critical_rate)
			{
				crit_1 = true;
			}

			if (crit_0 && !crit_1)
			{
				message =
					std::string(_attacker->name) + " used " + name + "!\n" +
					"First Hit (Critical): " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= (_attacker->physical_damage * 0.7) * 1.5) + " Health\n" + 
					"Second Hit: " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= _attacker->physical_damage * 0.7) + " Health";
			}

			else if (!crit_0 && crit_1)
			{
				message =
					std::string(_attacker->name) + " used " + name + "!\n" +
					"First Hit: " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= _attacker->physical_damage * 0.7) + " Health\n" +
					"Second Hit (Critical): " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= (_attacker->physical_damage * 0.7) * 1.5) + " Health";
			}

			else if (crit_0 && crit_1)
			{
				message =
					std::string(_attacker->name) + " used " + name + "!\n" +
					"First Hit (Critical): " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= (_attacker->physical_damage * 0.7) * 1.5) + " Health\n" +
					"Second Hit (Critical): " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= (_attacker->physical_damage * 0.7) * 1.5) + " Health";

			}

			message =
				std::string(_attacker->name) + " used " + name + "!\n" +
				"First Hit: " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= _attacker->physical_damage * 0.7) + " Health\n";
				"Second Hit: " + std::string(_target->name) + " lost " + std::to_string(_target->cur_health -= _attacker->physical_damage * 0.7) + " Health";
		}
		else
		{
			message = std::string(_attacker->name) + " used " + name + " but " + std::string(_target->name) + " dodged!";
		}
	}

	else
	{
		message = std::string(_attacker->name) + " tried to use " + name + "! But if failed due the lack of mana.";
	}

	return message;
}
	

	