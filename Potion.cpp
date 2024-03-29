#include "Potion.hpp";
#include "Renderer.hpp"

Potion::Potion(PotionType _type) : health_recovery{0}, mana_recovery{0}, Consumable("\0", 5)
{
	potionType = _type;

	switch (potionType)
	{
		case PotionType::MINOR_HEALTH_POTION:
			sprite = Sprite::MINOR_HEALTH_POTION;
			health_recovery = 5;
			name = "Minor Health Potion";
			description = "Restores +5 Health Points";
			break;
		case PotionType::MEDIUM_HEALTH_POTION:
			sprite = Sprite::MEDIUM_HEALTH_POTION;
			health_recovery = 10;
			name = "Medium Health Potion";
			description = "Restores +10 Health Points";
			break;
		case PotionType::GREATER_HEALTH_POTION:
			sprite = Sprite::GREATER_HEALTH_POTION;
			health_recovery = 15;
			name = "Greater Health Potion";
			description = "Restores +15 Health Points";
			break;
		case PotionType::MINOR_MANA_POTION:
			sprite = Sprite::MINOR_MANA_POTION;
			mana_recovery = 5;
			name = "Minor Mana Potion";
			description = "Restores +5 Mana Points";
			break;
		case PotionType::MEDIUM_MANA_POTION:
			sprite = Sprite::MEDIUM_MANA_POTION;
			mana_recovery = 10;
			name = "Medium Mana Potion";
			description = "Restores +10 Mana Points";
			break;
		case PotionType::GREATER_MANA_POTION:
			sprite = Sprite::GREATER_MANA_POTION;
			mana_recovery = 15;
			name = "Greater Mana Potion";
			description = "Restores +15 Mana Points";
			break;
	}
}

Potion::~Potion()
{

}