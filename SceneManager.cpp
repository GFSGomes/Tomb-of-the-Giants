#include "SceneManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "Portal.hpp"
#include "Scene.hpp"
#include "Light.hpp"
//#include "Weapon.hpp"
//#include "Armor.hpp"
//#include "Torch.hpp"
//#include "Potion.hpp"
//#include "Key.hpp"
#include "ItemDatabase.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	std::vector<std::shared_ptr<Portal>> PORTALs;

	/*** (1) SHARED POINTERS ***/
	std::shared_ptr<Player> player = std::make_shared<Player>(PLAYER);

	std::shared_ptr<Scene> scene_0	= std::make_shared<Scene>(8, 8);
	std::shared_ptr<Scene> secret_0 = std::make_shared<Scene>(4, 4);
	std::shared_ptr<Scene> scene_1	= std::make_shared<Scene>(10, 10);
		
	std::shared_ptr<Portal> scene_0_down  = std::make_shared<Portal>(Position::DOWN, scene_1);
	std::shared_ptr<Portal> scene_0_right = std::make_shared<Portal>(Position::RIGHT, secret_0, true, KeyType::SECRET_KEY);
	std::shared_ptr<Portal> secret_0_left = std::make_shared<Portal>(Position::LEFT, scene_0);
	std::shared_ptr<Portal> scene_1_up	  = std::make_shared<Portal>(Position::UP, scene_0);
	
	/*** (2) PORTAL PUSH_BACKS ***/
	PORTALs.push_back(scene_0_down);
	PORTALs.push_back(scene_0_right);
	PORTALs.push_back(secret_0_left);
	PORTALs.push_back(scene_1_up);

	/*** (3) SCENE OBJECT PUSH_BACKS ***/
	// A adição de itens na cena deve ser feita criando um ponteiro para o objeto externo desejado **
	player->SpawnAt(4, 5);
	scene_0->AddObject(player);
	scene_0->AddObject(scene_0_down);
	scene_0->AddObject(scene_0_right);
	scene_0->AddObject(std::make_shared<Key>(portalKey));
	scene_0->AddObject(std::make_shared<Weapon>(sword_Rapier));
	scene_0->AddObject(std::make_shared<Weapon>(sword_Zweihander));
	scene_0->AddObject(std::make_shared<Weapon>(axe_battleAxe));

	// SCENE_0_SECRET
	secret_0->AddObject(secret_0_left);

	// SCENE_1:
	scene_1->AddObject(scene_1_up);
	scene_1->AddObject(std::make_shared<Key>(secretKey));
	scene_1->AddObject(std::make_shared<Enemy>("Skeleton", 1, Sprite::SKELETON_FOOTMAN));
	scene_1->AddObject(std::make_shared<Enemy>("Skeleton", 1, Sprite::SKELETON_FOOTMAN));
	scene_1->AddObject(std::make_shared<Enemy>("Skeleton", 1, Sprite::SKELETON_FOOTMAN));


	/*** (4) FINDING PORTAL MIRRORS ***/
	for (short i = 0; i < PORTALs.size(); i++)
	{
		if (PORTALs[i]->mirror == nullptr)
		{
			PORTALs[i]->SearchMirrorInDestiny();
		}
	}


	/*** (5) START GAME ***/
	std::shared_ptr<Portal> activeScene = scene_0->LoadScene(); // First Scene;
	
	while (true)
	{
		if (!activeScene->scene->player)
		{
			activeScene->scene->AddObject(player);
		}

		// LoadScene() returns a portal;
		// When it return, a new While loop is called, loading a new destiny Scene;
		activeScene = activeScene->scene->LoadScene();
	}
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{

}