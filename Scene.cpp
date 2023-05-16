#include "Scene.hpp"
#include "GameInterfaceUI.hpp"
#include "InteractionUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Light.hpp"
#include "Portal.hpp"
#include "Slot.hpp"
#include "Global.hpp"
#include "Renderer.hpp"
#include <conio.h>
#include "Wall.hpp"

Scene::Scene(short _gridSizeX, short _gridSizeY) : grid{_gridSizeX, _gridSizeY}, currentScene{false}
{
	gridSizeX = _gridSizeX;
	gridSizeY = _gridSizeY;
}

Scene::~Scene()
{

}

void Scene::AddObject(std::shared_ptr<GameObject> obj)
{
	SceneOBJ.push_back(obj);

	if (std::dynamic_pointer_cast<Player>(obj))
	{
		player = std::dynamic_pointer_cast<Player>(obj);
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
		std::shared_ptr<Portal> spawnPoint;

		if (std::dynamic_pointer_cast<Portal>(obj) || std::dynamic_pointer_cast<Player>(obj) || std::dynamic_pointer_cast<Wall>(obj))
		{
			obj->SpawnAt(obj->posX, obj->posY);
		}
		else
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
				if (std::dynamic_pointer_cast<Item>(obj))
				{
					bool removeObject = UI_Interaction.Initialize(player, obj, SceneOBJ);
					
					if (removeObject)
					{
						SceneOBJ.erase(SceneOBJ.begin() + i);
					}
				}

				else if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
				{
					UI_Interaction.Initialize(player, enemy, SceneOBJ);
					
					if (!enemy->alive)
					{
						SceneOBJ.erase(SceneOBJ.begin() + i);
					}
				}

				//PORTAL
				else if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					if (portal->active)
					{
						loadPortal = portal;
						player->posX = portal->out->posX;
						player->posY = portal->out->posY;

						loadPortal->scene->AddObject(player);

						currentScene = false;
					}
					return;
				}
			}
		}

		if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
		{
			enemy->Actions(false, SceneOBJ);
		}
	}
}

void Scene::LoadScene()
{
	GridSizeX = gridSizeX;
	GridSizeY = gridSizeY;

	srand(time(0));

	currentScene = true;

	SpawnObjects();

	while (currentScene)
	{
		if (GameOver){
			currentScene = false;
			return;
		}

		UI_GameInterface.Initialize(player);

		grid.UpdateGrid(SceneOBJ, player);

		UI_GameInterface.Input(player, SceneOBJ);

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
					enemy->Actions(false, SceneOBJ);
				}
			}
		}
	}

	loadPortal->scene->LoadScene();
}