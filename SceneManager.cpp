#include "SceneManager.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	Scene scene_00{12, 6};
	scene_00.AddObject(std::make_shared<Player>(PLAYER)); // Ponteiro para o player
	scene_00.AddObject(std::make_shared<Weapon>(axe));
	scene_00.AddObject(std::make_shared<Potion>(potion));
	scene_00.AddObject(std::make_shared<Enemy>(spider));
	scene_00.AddObject(std::make_shared<Enemy>(spider));
	scene_00.AddObject(std::make_shared<Enemy>(undead));
	scene_00.AddObject(std::make_shared<Enemy>(undead));
	scene_00.player->SpawnAt(0, 0);
	Scenes = {scene_00};
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{
	for (short i = 0; i < Scenes.size(); i++)
	{
		Scenes[i].LoadScene();

		if (!Scenes[i].currentScene)
		{
			if (i < Scenes.size() - 1)
			{
				if (!GameOver)
				{
					Scenes[i++].LoadScene();
				}
			}
		}
	}
}