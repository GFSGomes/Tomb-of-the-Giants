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
	std::vector<std::shared_ptr<Portal>> PORTALs;

	#pragma region ESPECIFIC_OBJECTS
	// Unique Pointers
	std::shared_ptr<Player> player = std::make_shared<Player>(PLAYER);
	// SCENEs
	std::shared_ptr<Scene> scene_0 = std::make_shared<Scene>(8, 8);
	std::shared_ptr<Scene> scene_1 = std::make_shared<Scene>(6, 6);
	// PORTALs
	std::shared_ptr<Portal> _00_down = std::make_shared<Portal>(Position::DOWN, scene_1, true);
	std::shared_ptr<Portal> _01_up = std::make_shared<Portal>(Position::UP, scene_0);
	#pragma endregion
	
	// PORTAL_REGISTRATION
	PORTALs.push_back(_00_down);
	PORTALs.push_back(_01_up);

	#pragma region SCENE_OBJECT_PUSHING
	// SCENE_0:
	player->SpawnAt(4, 5);
	scene_0->AddObject(player);
	scene_0->AddObject(_00_down);

	// SCENE_1:
	scene_1->AddObject(_01_up);
	#pragma endregion

	// FINDING_PORTALS_MIRRORS
	for (short i = 0; i < PORTALs.size(); i++)
	{
		if (PORTALs[i]->mirror == nullptr)
		{
			PORTALs[i]->SearchMirrorInDestiny();
		}
	}

	// LOAD_FIRST_SCENE
	std::shared_ptr<Portal> activeScene = scene_0->LoadScene();
	
	// SCENE_LOOPS
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