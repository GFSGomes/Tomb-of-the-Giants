#include "SceneManager.hpp"

bool GameOver = false;

SceneManager sceneManager;

SceneManager::SceneManager()
{
	Scene scene_00{8, 8};
	scene_00.AddObject(std::make_shared<Player>(PLAYER)); //Ponteiro para o player
	scene_00.AddObject(std::make_shared<Enemy>("Wolf", 1));
	scene_00.AddObject(std::make_shared<Enemy>("Wolf", 1));
	scene_00.AddObject(std::make_shared<Enemy>("Wolf", 1));
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
					Scenes[i + 1].LoadScene();
				}
			}
		}
	}
}