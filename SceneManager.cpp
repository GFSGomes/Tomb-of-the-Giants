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
	std::shared_ptr<Scene> scene_1 = std::make_shared<Scene>(6, 6);

	// PORTALs
	// [!] Cuidado ao posicionar portais: não podem observar as variáveis de tamanho da Grid
	// Ficar atento às dimensões da cena origem;
	std::shared_ptr<Portal> S0_T1 = std::make_shared<Portal>(4, 8, scene_0, scene_1, true);
	std::shared_ptr<Portal> S1_T0 = std::make_shared<Portal>(3, 0, scene_1, scene_0, true);

	// Setting MIRRORS
	S0_T1->mirror = S1_T0;
	S1_T0->mirror = S0_T1;

	// SCENE_0:
	player->SpawnAt(4, 5);
	scene_0->AddObject(player);
	scene_0->AddObject(std::make_shared<Key>(KeyType::PORTAL_KEY));
	scene_0->AddObject(S0_T1);

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