#include "ItemDatabase.hpp"

#pragma region DATABASE_ITENS_INIT
																 // P    M    A     C     C
																 // d    d    c     c     d
Weapon sword_shortSword{WeaponType::OH_SWORD, "Short Sword", "",	5,   1,   3,    5, 1.15};
Weapon sword_longSword{WeaponType::OH_SWORD, "Long Sword", "",		7,   1,   3,  7.5, 1.75};
Weapon sword_Falchion{WeaponType::OH_SWORD, "Falchion", "",			9,   0,   1,    5,    2};
Weapon sword_Rapier{WeaponType::OH_SWORD, "Rapier", "",				4,   0,   5,   20,    2}; //
Weapon sword_Claymore{WeaponType::TH_SWORD, "Claymore", "",			9,   0,   1,   10,  2.5};
Weapon sword_Zweihander{WeaponType::TH_SWORD, "Zweihander", "",	   12,   0,   2,  7.6,    3}; //
Weapon axe_woodAxe{WeaponType::OH_AXE, "Wood Axe", "",			  5.5,   0,   2,   10,  1.5};
Weapon axe_hatchet{WeaponType::OH_AXE, "Hatchet", "",				8,   0,   2, 12.5,  1.5};
Weapon axe_steelAxe{WeaponType::OH_AXE, "Steel Axe", "",		   10,   0,   0,   15,    2};
Weapon axe_battleAxe{WeaponType::TH_AXE, "Battle Axe", "",		   12,   0,   0,   10,    3}; //
Weapon dagger_dirk{WeaponType::DAGGER, "Dirk", "",					3,   0,   5,   10,  1.5};
Weapon dagger_stilleto{WeaponType::DAGGER, "Stilleto", "",			4,   1,   7,    6, 1.75};
Weapon dagger_kriss{WeaponType::DAGGER, "Kriss", "",				5,   2,  10, 12.5,    2};
Weapon dagger_alkavine{WeaponType::DAGGER, "Alkavine's Dagger", "", 5,   3,  20,   15,    2};
Weapon bow_oakBow{WeaponType::BOW, "Oak Bow", "",					3,   0,  10,    5,    0};
Weapon bow_steelBow{WeaponType::BOW, "Steel Bow", "",				5,   0,  10,    5,    0};
Weapon bow_silverBow{WeaponType::BOW, "Silver Bow", "",				7,   2,  15,    5, 1.15};
Weapon bow_elvenBow{WeaponType::BOW, "Elven Bow", "",				8,   3,  15,    5, 1.75};
Weapon staff_oakStaff{WeaponType::STAFF, "Oak Staff", "",			1,   4,   0,    0,    0};
Weapon staff_arcaneStaff{WeaponType::STAFF, "Arcane Staff", "",		1,   6,   0,    0,    0};
Weapon staff_archmageStaff{WeaponType::STAFF, "Archmage Staff", "", 1,   8,   3,    0,    0};
Weapon staff_ishvarStaff{WeaponType::STAFF, "Ishvar's Staff", "",	1,  10,   5,    0,    0};

Armor lightBody_soldierUniform{ArmorType::BODY, Sprite::LIGHT_BODY, "Soldier Uniform", "", 4, 1, 8, 5, 0, 0, 0, 2, 1};
Armor lightBody_wizardRobe{ArmorType::BODY, Sprite::LIGHT_BODY, "Wizard Robe", "", 3, 8, 4, 0, 0, 0, 3};
Armor lightBody_rangerClothes{ArmorType::BODY, Sprite::LIGHT_BODY, "Ranger Clothes", "", 5, 2, 10, 10, 0, 0, 0, 3, 2};
Armor mediumBody_gambeson{ArmorType::BODY, Sprite::MEDIUM_BODY, "Gambeson", "", 8, 4, 3, 1};
Armor mediumBody_leatherArmor{ArmorType::BODY, Sprite::MEDIUM_BODY, "Leather Armor", "", 10, 6, 1, 0, 2, 2};
Armor heavyBody_ironPlate{ArmorType::BODY, Sprite::HEAVY_BODY, "Iron Plate", "", 13, 2, 0, 0, 4, 4};
Armor heavyBody_steelPlate{ArmorType::BODY, Sprite::HEAVY_BODY, "Steel Plate", "", 16, 5, 0, 0, 5, 5};
Armor heavyBody_necrowolf{ArmorType::BODY, Sprite::HEAVY_BODY, "Necrowolf's Plate", "An ancient plate made to protect agains spells.", 8, 20, 0, 0, 5, 5};

Armor lightHead_hood{ArmorType::HEAD, Sprite::LIGHT_HEAD, "Hood", "", 4, 3, 4, 5, 0, 0, 2, 5};
Armor heavyHead_bascinet{ArmorType::HEAD, Sprite::LIGHT_HEAD, "Bascinet", "", 12, 3, 0, 5};

Armor heavyLegs_greaves{ArmorType::LEGS, Sprite::NONE, "Greaves", "", 5, 2, 3};
Armor heavyArms_steelGaunlets{ArmorType::ARMS, Sprite::NONE, "Steel Gaunlets", "", 5, 2, 0, 0, 2};

Key portalKey{KeyType::PORTAL_KEY};
Key secretKey{KeyType::SECRET_KEY};
Key chestKey{KeyType::CHEST_KEY};
#pragma endregion //*** INICIALIZAÇÃO DOS OBJETOS ***

ItemDatabase::ItemDatabase() : ItemDB{
	std::make_shared<Weapon>(sword_shortSword),
	std::make_shared<Weapon>(sword_longSword),
	std::make_shared<Weapon>(sword_Falchion),
	std::make_shared<Weapon>(sword_Rapier),
	std::make_shared<Weapon>(sword_Claymore),
	std::make_shared<Weapon>(sword_Zweihander),
	std::make_shared<Weapon>(axe_woodAxe),
	std::make_shared<Weapon>(axe_hatchet),
	std::make_shared<Weapon>(axe_steelAxe),
	std::make_shared<Weapon>(axe_battleAxe),
	std::make_shared<Weapon>(dagger_dirk),
	std::make_shared<Weapon>(dagger_stilleto),
	std::make_shared<Weapon>(dagger_kriss),
	std::make_shared<Weapon>(dagger_alkavine),
	std::make_shared<Weapon>(bow_oakBow),
	std::make_shared<Weapon>(bow_steelBow),
	std::make_shared<Weapon>(bow_silverBow),
	std::make_shared<Weapon>(bow_elvenBow),
	std::make_shared<Weapon>(staff_oakStaff),
	std::make_shared<Weapon>(staff_arcaneStaff),
	std::make_shared<Weapon>(staff_archmageStaff),
	std::make_shared<Weapon>(staff_ishvarStaff),
	//...
}
{}

std::vector<std::shared_ptr<Item>> ItemDatabase::GenerateRandomItem() // Acessados por inimigos para gerar drops aleatórios em um vetor;
{
	short amount{rand() % 4 + 1}; // 1 ~ 4
	std::vector<std::shared_ptr<Item>> Drops;

	for (short i = 0; i < amount; i++)
	{
		short drop = rand() % 101; // 0 ~ 100 -> Cada item deve ter uma propriedade de dropRate;
		short chosenItem = rand() % ItemDB.size();

		if (drop >= (100 - ItemDB[chosenItem]->dropRate)) // 100 - item->dropRate == dificuldade
		{

		}
	}

	return Drops;
}
