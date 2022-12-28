#include "Scene.hpp"
#include "GameMenu.hpp"
#include "Equipment.hpp"
#include "EncounterMenu.hpp"
#include "Torch.hpp"

Scene::Scene(short gridSizeX, short gridSizeY) : grid{gridSizeX, gridSizeY}, currentScene{false}
{

}

Scene::~Scene()
{

}

void Scene::AddObject(std::shared_ptr<GameObject> obj)
{
	SceneOBJ.push_back(obj);

	if (std::shared_ptr<Player> _player = std::dynamic_pointer_cast<Player>(obj))
	{
		player = _player;
	}

	if (player != nullptr)
	{
		for (std::shared_ptr<Light> light : player->FOV)
		{
			SceneOBJ.push_back(light);
		}
	}
}

void Scene::SpawnObjects()
{
	for (std::shared_ptr<GameObject> obj : SceneOBJ)
	{
		obj->SpawnRandom();

		// Prevenindo sobreposição durante o spawn;
		for (std::shared_ptr<GameObject> other : SceneOBJ)
		{
			if (other != obj)
			{
				while (obj->posX == other->posX && obj->posY == other->posY)
				{
					obj->SpawnRandom();
				}
			}
		}
	}

	if (player != nullptr)
	{
		for (std::shared_ptr<Light> _light : player->FOV)
		{
			SceneOBJ.push_back(_light);
		}
		player->UpdateFOV();
	}
}

void Scene::Interaction()
{
	for (short i = 0; i < SceneOBJ.size(); i++)
	{
		if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
		{
			if (player->posX == enemy->posX && player->posY == enemy->posY)
			{
				encounterMenu.Initialize(player, enemy);
			}
		}

		if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(SceneOBJ[i]))
		{
			if (player->posX == item->posX && player->posY == item->posY)
			{
				if (std::shared_ptr<Torch> torch = std::dynamic_pointer_cast<Torch>(SceneOBJ[i]))
				{
					torch->Use();
				}

				else
				{
					player->inventory.AddItem((std::shared_ptr<Item>) item, 1);
				}

				SceneOBJ.erase(SceneOBJ.begin() + i);
			}
		}
	}
}

void Scene::LoadScene()
{
	srand(time(0));
	bool currentScene = true;
	SpawnObjects();

	while (currentScene)
	{
		gameMenu.Initialize(player);
		grid.UpdateGrid(SceneOBJ, player);
		gameMenu.Input(player);
		Interaction();
	}
}