#include "SceneManager.hpp"
#include "Key.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Renderer.hpp"
#include "Potion.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Wall.hpp"
#include "Portal.hpp"
#include "Scene.hpp"
#include "Torch.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	// Unique Pointers
	std::shared_ptr<Player> player = std::make_shared<Player>(PLAYER);

	// SCENEs
	std::shared_ptr<Scene> scene_0 = std::make_shared<Scene>(8, 8);
	std::shared_ptr<Scene> scene_0_SECRET = std::make_shared<Scene>(4, 4);

	std::shared_ptr<Scene> scene_1 = std::make_shared<Scene>(6, 6);

	// PORTALs
	// [!] Cuidado ao posicionar portais: não podem observar as variáveis de tamanho da Grid
	// Ficar atento às dimensões da cena origem;
	std::shared_ptr<Portal> S0_T1 = std::make_shared<Portal>(4, 8, scene_0, scene_1, true);
	std::shared_ptr<Portal> S1_T0 = std::make_shared<Portal>(3, 0, scene_1, scene_0, true);
	std::shared_ptr<Portal> S0_SECRET = std::make_shared<Portal>(8, 4, scene_0, scene_0_SECRET, true, KeyType::SECRET_KEY);
	std::shared_ptr<Portal> S0_SECRET_EXIT = std::make_shared<Portal>(0, 2, scene_0_SECRET, scene_0, true, KeyType::SECRET_KEY);

	// Setting MIRRORS
	S0_T1->mirror = S1_T0;
	S1_T0->mirror = S0_T1;
	S0_SECRET->mirror = S0_SECRET_EXIT;
	S0_SECRET_EXIT->mirror = S0_SECRET;

	// SCENE_0:
	player->SpawnAt(4, 5);
	scene_0->AddObject(player);
	scene_0->AddObject(std::make_shared<Key>(KeyType::SECRET_KEY));
	scene_0->AddObject(std::make_shared<Enemy>("Cave Spider", 2, Sprite::SPIDER));
	scene_0->AddObject(std::make_shared<Enemy>("Cave Spider", 2, Sprite::SPIDER));
	scene_0->AddObject(std::make_shared<Enemy>("Cave Spider", 2, Sprite::SPIDER));
	scene_0->AddObject(std::make_shared<Enemy>("Spider Queen", 3, Sprite::SPIDER));
	scene_0->AddObject(std::make_shared<Torch>());
	scene_0->AddObject(std::make_shared<Potion>(PotionType::MINOR_HEALTH_POTION));
	scene_0->AddObject(S0_T1);
	scene_0->AddObject(S0_SECRET);

	scene_0_SECRET->AddObject(S0_SECRET_EXIT);
	scene_0_SECRET->AddObject(std::make_shared<Key>(KeyType::PORTAL_KEY));
	scene_0_SECRET->AddObject(std::make_shared<Potion>(PotionType::GREATER_HEALTH_POTION));
	scene_0_SECRET->AddObject(std::make_shared<Potion>(PotionType::GREATER_MANA_POTION));

	// SCENE_1:
	scene_1->AddObject(S1_T0);

	_Scenes = {scene_0};
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{
	_Scenes[0]->LoadScene();
}