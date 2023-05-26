#pragma once
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Torch.hpp"
#include "Potion.hpp"
#include "Key.hpp"
#include <vector>
#include "Renderer.hpp"

struct ItemDatabase
{
	std::vector<std::shared_ptr<Item>> ItemDB;

	ItemDatabase();

	std::vector<std::shared_ptr<Item>> GenerateRandomItem();
};
extern Weapon sword_shortSword;
extern Weapon sword_longSword;
extern Weapon sword_Falchion;
extern Weapon sword_Rapier;
extern Weapon sword_Claymore;
extern Weapon sword_Zweihander;
extern Weapon axe_woodAxe;
extern Weapon axe_hatchet;
extern Weapon axe_steelAxe;
extern Weapon axe_battleAxe;
extern Weapon dagger_dirk;
extern Weapon dagger_stilleto;
extern Weapon dagger_kriss;
extern Weapon dagger_alkavine;
extern Weapon bow_oakBow;
extern Weapon bow_steelBow;
extern Weapon bow_silverBow;
extern Weapon bow_elvenBow;
extern Weapon staff_oakStaff;
extern Weapon staff_arcaneStaff;
extern Weapon staff_archmageStaff;
extern Weapon staff_ishvarStaff;

extern Armor lightBody_soldierUniform;
extern Armor lightBody_wizardRobe;
extern Armor lightBody_rangerClothes;
extern Armor mediumBody_gambeson;
extern Armor mediumBody_leatherArmor;
extern Armor heavyBody_ironPlate;
extern Armor heavyBody_steelPlate;
extern Armor heavyBody_necrowolf;

extern Armor lightHead_hood;
extern Armor heavyHead_bascinet;

extern Armor heavyLegs_greaves;

extern Armor heavyArms_steelGaunlets;

extern Key portalKey;
extern Key secretKey;
extern Key chestKey;
