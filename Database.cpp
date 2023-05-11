#include "Database.hpp"

Enemy spider("Spider", 1, Sprite::SPIDER);
Enemy undead("Skeleton Footman", 2, Sprite::SKELENTON_FOOTMAN);

Weapon sword(WeaponType::SWORD, "Short Sword", "A versatile sword that can be used with a shield.", 10, 0);
Weapon axe(WeaponType::AXE, "Battle Axe", "A double edged axe made of steel.", 24, 0);

Potion potion(PotionType::MEDIUM_HEALTH_POTION);