#include "SceneManager.hpp"
#include "Portal.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Potion.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Wall.hpp"
#include "Torch.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	std::shared_ptr<Player> _Player = std::make_shared<Player>(PLAYER);
	_Player->SpawnAt(0, 0);

	std::shared_ptr<Scene> scene_00 = std::make_shared<Scene>(8, 9);
	std::shared_ptr<Scene> scene_01 = std::make_shared<Scene>(16, 15);
	std::shared_ptr<Scene> scene_02 = std::make_shared<Scene>(32, 15);

	std::shared_ptr<Portal> _0_1 = std::make_shared<Portal>(7, 4);
	std::shared_ptr<Portal> _1_0 = std::make_shared<Portal>(0, 7);
	std::shared_ptr<Portal> _1_2 = std::make_shared<Portal>(15, 7);
	std::shared_ptr<Portal> _2_1 = std::make_shared<Portal>(0, 7);

	_0_1->out = _1_0;
	_1_0->out = _0_1;

	_1_2->out = _2_1;
	_2_1->out = _1_2;

	_1_0->scene = scene_00;
	_0_1->scene = scene_01;
	_2_1->scene = scene_01;
	_1_2->scene = scene_02;

	std::shared_ptr<Weapon> alkavine_dagger = std::make_shared<Weapon>(WeaponType::DAGGER, "ALVAVINE's DAGGER", "Ideal for shorter persons.", 3, 1, 5, 10, 2);
	std::shared_ptr<Weapon> necrowolf_sword = std::make_shared<Weapon>(WeaponType::SWORD, "NECROWOLF's SWORD", "Especial development weapon.", 7, 6, 99, 10, 7);
	std::shared_ptr<Weapon> short_sword		= std::make_shared<Weapon>(WeaponType::SWORD, "SHORT SWORD", "A versatile and sharp edge.", 4, 0, 0, 10, 3);
	std::shared_ptr<Weapon> battle_axe		= std::make_shared<Weapon>(WeaponType::AXE, "BATTLE AXE", "Crush enemy skulls!", 5, 0, 0, 5, 3);

	std::shared_ptr<Potion> health_0 = std::make_shared<Potion>(PotionType::MINOR_HEALTH_POTION);
	std::shared_ptr<Potion> mana_0	 = std::make_shared<Potion>(PotionType::MINOR_MANA_POTION);

	scene_00->AddObject(_Player);
	for (short i = 0; i < 5; i++)
	{
		scene_00->AddObject(std::make_shared<Wall>(i, 1));
		scene_00->AddObject(std::make_shared<Wall>(i, scene_00->gridSizeY));
	}

	scene_00->AddObject(std::make_shared<Enemy>("CAVE SPIDER", 1, Sprite::SPIDER));
	scene_00->AddObject(std::make_shared<Enemy>("CAVE SPIDER", 1, Sprite::SPIDER));
	scene_00->AddObject(std::make_shared<Enemy>("CAVE SPIDER", 1, Sprite::SPIDER));
	scene_00->AddObject(_0_1);

	scene_01->AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_FOOTMAN));
	scene_01->AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_FOOTMAN));
	scene_01->AddObject(battle_axe);
	scene_01->AddObject(health_0);
	scene_01->AddObject(mana_0);
	scene_01->AddObject(_1_0);
	scene_01->AddObject(_1_2);

	scene_02->AddObject(std::make_shared<Enemy>("SKELETON GIANT", 3, Sprite::SKELETON_GIANT));
	scene_02->AddObject(std::make_shared<Enemy>("SKELETON GIANT", 3, Sprite::SKELETON_GIANT));
	scene_02->AddObject(std::make_shared<Enemy>("SKELETON GIANT", 3, Sprite::SKELETON_GIANT));
	scene_02->AddObject(alkavine_dagger);
	scene_02->AddObject(health_0);
	scene_02->AddObject(mana_0);
	scene_02->AddObject(_2_1);

	_Scenes = {scene_00, scene_01, scene_02};
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{
	_Scenes[0]->LoadScene();
}