#include "Database.hpp"

Enemy forestSpider("FOREST SPIDER", 1, Sprite::SPIDER);
Enemy skeletonFootman("SKELETON FOOTMAN", 3, Sprite::SKULL);

Weapon shortSword(WeaponType::SWORD, "SHORT SWORD", "A versatile sword that can be used with a shield.", 8, 0);
Weapon longSword(WeaponType::SWORD, "LONG SWORD", "A versatile sword to use with both hands.", 12, 0); 

Weapon hatchet(WeaponType::AXE, "HATCHET", "A hatchet used to cut wood.", 9, 0);

Potion hp1("Health", PotionType::MEDIUM_MANA_POTION);