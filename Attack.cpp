#include "Attack.hpp"
#include <string>

Attack::Attack()
{

}

Attack::~Attack()
{

}

std::string Attack::Use(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target)
{
	return std::string(attacker->name) + " attacked: " + std::string(target->name) + " lost " + std::to_string(attacker->physical_pwr) + " of Health\n";
}