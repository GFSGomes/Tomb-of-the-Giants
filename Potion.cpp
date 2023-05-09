#include "Potion.hpp";
Potion::Potion(const char* _name, PotionType _type) : health_recovery{0}, mana_recovery{0}, Item(_name, 3) //Stack
{
	name = _name;
	_type = _type;

	switch (_type)
	{
		case PotionType::MINOR_HEALTH_POTION:
			health_recovery = 5;
			break;
		case PotionType::MEDIUM_HEALTH_POTION:
			health_recovery = 10;
			break;
		case PotionType::GREAT_HEALTH_POTION:
			health_recovery = 15;
			break;
		case PotionType::MINOR_MANA_POTION:
			mana_recovery = 5;
			break;
		case PotionType::MEDIUM_MANA_POTION:
			mana_recovery = 10;
			break;
		case PotionType::GREAT_MANA_POTION:
			mana_recovery = 15;
			break;
	}
}

Potion::~Potion()
{

}