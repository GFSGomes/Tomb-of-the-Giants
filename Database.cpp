#include "Database.hpp"

Enemy spider("Spider", 1, Sprite::SPIDER);
Enemy undead("Skeleton Footman", 2, Sprite::SKELETON_FOOTMAN);

Weapon sword(WeaponType::SWORD, "Short Sword", "A versatile sword that can be used with a shield.", 5, 0);
Weapon axe(WeaponType::AXE, "Battle Axe", "A double edged axe made of steel.", 5, 0);

Potion potion(PotionType::MEDIUM_HEALTH_POTION);