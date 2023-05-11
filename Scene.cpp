#include "Scene.hpp"
#include "GameInterfaceUI.hpp"
#include "InteractionUI.hpp"
#include "Equipment.hpp"
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
		if (std::shared_ptr<GameObject> obj = std::dynamic_pointer_cast<GameObject>(SceneOBJ[i]))
		{
			if (player->posX == obj->posX && player->posY == obj->posY)
			{
				if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(obj))
				{
					bool removeObject = UI_Interaction.Initialize(player, item);
					
					if (removeObject)
					{
						SceneOBJ.erase(SceneOBJ.begin() + i);
					}
					else
					{
						break;
					}
				}

				else if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
				{
					UI_Interaction.Initialize(player, enemy);
					
					if (!enemy->alive)
					{
						SceneOBJ.erase(SceneOBJ.begin() + i);
					}
				}
			}
		}

		if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
		{
			enemy->Actions(false);
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
		if (GameOver){
			currentScene = false;
			return;
		}

		UI_GameInterface.Initialize(player);

		grid.UpdateGrid(SceneOBJ, player);

		UI_GameInterface.Input(player);

		if (IsPaused)
		{
			continue;
		}
		else
		{
			Interaction();

			for (short i = 0; i < SceneOBJ.size(); i++)
			{
				if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
				{
					enemy->Actions(false);
				}
			}
		}
	}
}