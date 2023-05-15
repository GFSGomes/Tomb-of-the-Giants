#include "SceneManager.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	std::shared_ptr<Player> _Player = std::make_shared<Player>(PLAYER);
	_Player->SpawnAt(0, 0);

	std::shared_ptr<Scene> scene_00 = std::make_shared<Scene>(8, 9);
	std::shared_ptr<Scene> scene_01 = std::make_shared<Scene>(16, 15);
	std::shared_ptr<Scene> scene_02 = std::make_shared<Scene>(32, 15);

	std::shared_ptr<Portal> _00 = std::make_shared<Portal>(7, 5);
	std::shared_ptr<Portal> _01 = std::make_shared<Portal>(15, 7);
	std::shared_ptr<Portal> _02 = std::make_shared<Portal>(31, 7);
	
	_00->scene = scene_00;
	_01->scene = scene_01;
	_02->scene = scene_02;

	std::shared_ptr<Enemy> cave_spider		= std::make_shared<Enemy>("CAVE SPIDER", 1, Sprite::SPIDER);
	std::shared_ptr<Enemy> skeleton_footman = std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_FOOTMAN);
	std::shared_ptr<Enemy> skeleton_giant	= std::make_shared<Enemy>("SKELETON GIANT", 3, Sprite::SKELETON_GIANT);

	std::shared_ptr<Weapon> alkavine_dagger = std::make_shared<Weapon>(WeaponType::DAGGER, "ALVAVINE's DAGGER", "Ideal for shorter persons.", 3, 1, 5, 10, 2);
	std::shared_ptr<Weapon> necrowolf_sword = std::make_shared<Weapon>(WeaponType::SWORD, "NECROWOLF's SWORD", "Especial development weapon.", 7, 6, 99, 10, 7);
	std::shared_ptr<Weapon> short_sword		= std::make_shared<Weapon>(WeaponType::SWORD, "SHORT SWORD", "A versatile and sharp edge.", 4, 0, 0, 10, 3);
	std::shared_ptr<Weapon> battle_axe		= std::make_shared<Weapon>(WeaponType::AXE, "BATTLE AXE", "Crush enemy skulls!", 5, 0, 0, 5, 3);

	std::shared_ptr<Potion> health_0 = std::make_shared<Potion>(PotionType::MINOR_HEALTH_POTION);
	std::shared_ptr<Potion> mana_0	 = std::make_shared<Potion>(PotionType::MINOR_MANA_POTION);

	scene_00->AddObject(_Player);
	scene_00->AddObject(cave_spider);
	scene_00->AddObject(cave_spider);
	scene_00->AddObject(cave_spider);
	scene_00->AddObject(short_sword);
	scene_00->AddObject(health_0);
	scene_00->AddObject(_01);

	scene_01->AddObject(skeleton_footman);
	scene_01->AddObject(skeleton_footman);
	scene_01->AddObject(skeleton_footman);
	scene_01->AddObject(battle_axe);
	scene_01->AddObject(health_0);
	scene_01->AddObject(mana_0);
	scene_01->AddObject(_00);
	scene_01->AddObject(_02);

	scene_01->AddObject(skeleton_giant);
	scene_01->AddObject(skeleton_giant);
	scene_01->AddObject(skeleton_giant);
	scene_01->AddObject(alkavine_dagger);
	scene_01->AddObject(health_0);
	scene_01->AddObject(mana_0);
	scene_01->AddObject(_01);

	_Scenes = {scene_00, scene_01, scene_02};
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{
	_Scenes[0]->LoadScene();
}