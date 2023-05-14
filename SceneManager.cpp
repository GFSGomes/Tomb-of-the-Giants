#include "SceneManager.hpp"

bool GameOver = false;

SceneManager::SceneManager()
{
	Scene scene_00{22, 10};
	Scene scene_01{14, 3};
	Scene scene_02{22, 6};

	scene_00.AddObject(std::make_shared<Player>(PLAYER)); // Ponteiro para o player
	scene_00.AddObject(std::make_shared<Potion>(PotionType::GREATER_HEALTH_POTION));
	scene_00.AddObject(std::make_shared<Potion>(PotionType::GREATER_MANA_POTION));
	scene_00.AddObject(std::make_shared<Weapon>(WeaponType::DAGGER, "Alkavine's Dagger", "Ideal for short persons.", 5, 1, 5, 10, 3));
	scene_00.AddObject(std::make_shared<Enemy>("SPIDER", 1, Sprite::SPIDER));
	scene_00.AddObject(std::make_shared<Enemy>("SPIDER", 1, Sprite::SPIDER));
	scene_00.AddObject(std::make_shared<Enemy>("SPIDER", 1, Sprite::SPIDER));
	scene_00.AddObject(std::make_shared<Portal>(0, 0));
	scene_00.AddObject(std::make_shared<Portal>(21, 9));
	scene_00.player->SpawnAt(0, 0);

	scene_01.AddObject(std::make_shared<Player>(PLAYER)); // Ponteiro para o player
	scene_01.AddObject(std::make_shared<Potion>(PotionType::GREATER_HEALTH_POTION));
	scene_01.AddObject(std::make_shared<Potion>(PotionType::GREATER_MANA_POTION));
	scene_01.AddObject(std::make_shared<Weapon>(WeaponType::DAGGER, "Alkavine's Dagger", "Ideal for short persons.", 5, 1, 5, 10, 3));
	scene_01.AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_FOOTMAN));
	scene_01.AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_FOOTMAN));
	scene_01.AddObject(std::make_shared<Portal>(0, 0));
	scene_01.AddObject(std::make_shared<Portal>(13, 2));
	scene_01.player->SpawnAt(0, 0);

	scene_02.AddObject(std::make_shared<Player>(PLAYER)); // Ponteiro para o player
	scene_02.AddObject(std::make_shared<Potion>(PotionType::GREATER_HEALTH_POTION));
	scene_02.AddObject(std::make_shared<Potion>(PotionType::GREATER_MANA_POTION));
	scene_02.AddObject(std::make_shared<Weapon>(WeaponType::DAGGER, "Alkavine's Dagger", "Ideal for short persons.", 5, 1, 5, 10, 3));
	scene_02.AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_GIANT));
	scene_02.AddObject(std::make_shared<Enemy>("SKELETON FOOTMAN", 2, Sprite::SKELETON_GIANT));
	scene_02.AddObject(std::make_shared<Portal>(0, 0));
	scene_02.AddObject(std::make_shared<Portal>(21, 5));
	scene_02.player->SpawnAt(0, 0);

	Scenes = {scene_00, scene_01, scene_02};
}

SceneManager::~SceneManager()
{

}

void SceneManager::StartGame()
{
	for (short i = 0; i < Scenes.size(); i++)
	{
		GridSizeX = Scenes[i].gridSizeX;
		GridSizeY = Scenes[i].gridSizeY;
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