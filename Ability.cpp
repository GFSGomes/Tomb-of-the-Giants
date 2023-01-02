#include "Ability.hpp"

Ability::Ability() : cost{0}, baseBonus{0}, bonusMultiplier{1}, requiredAccuracy{0}
{

}

Ability::~Ability()
{

}

std::string Ability::Cast(std::shared_ptr<Entity>, std::shared_ptr<Entity>)
{
	return "";
}