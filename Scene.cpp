#include "Scene.hpp"
#include "GameInterfaceUI.hpp"
#include "InteractionUI.hpp"

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
		if (!std::dynamic_pointer_cast<Portal>(obj) || !std::dynamic_pointer_cast<Player>(obj))
		{
			obj->SpawnRandom();
		}

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
				}

				else if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
				{
					UI_Interaction.Initialize(player, enemy);
					
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
						loadPortal->scene->AddObject(player);
						for (short i = 0; i < player->inventory.Container.size(); i++)
						{
							loadPortal->scene->player->inventory.AddItem(player->inventory.Container[i].item, player->inventory.Container[i].amount);
						}
						currentScene = false;
					}
					return;
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
	GridSizeX = gridSizeX;
	GridSizeY = gridSizeY;

	srand(time(0));

	currentScene = true;

	SpawnObjects();

	system("cls");
	Renderer::Dialog("Done. Press any key to continue...");
	_getch();

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

	loadPortal->scene->LoadScene();
}