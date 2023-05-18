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

Scene::Scene(short _gridSizeX, short _gridSizeY) : grid{_gridSizeX, _gridSizeY}, scene_log{"\0"}, currentScene{false}
{
	gridSizeX = _gridSizeX + 1;
	gridSizeY = _gridSizeY + 1;
}

Scene::~Scene()
{

}

void Scene::AddObject(std::shared_ptr<GameObject> obj)
{
	SceneOBJ.push_back(obj);

	if (player == nullptr)
	{
		if (std::dynamic_pointer_cast<Player>(obj))
		{
			player = std::dynamic_pointer_cast<Player>(obj);

			if (player == obj)
			{
				for (std::shared_ptr<Light> light : player->FOV)
				{
					SceneOBJ.push_back(light);
				}
			}
		}
	}
}

void Scene::SpawnObjects()
{
	for (std::shared_ptr<GameObject> obj : SceneOBJ)
	{
		if (std::dynamic_pointer_cast<Portal>(obj) ||
			std::dynamic_pointer_cast<Player>(obj) ||
			std::dynamic_pointer_cast<Wall>(obj) ||
			std::dynamic_pointer_cast<Light>(obj) ||
			std::dynamic_pointer_cast<Key>(obj)
			)
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
		player->UpdateFOV();
	}
}

void Scene::Interaction()
{
	bool has_key = false;

	for (short i = 0; i < SceneOBJ.size(); i++)
	{
		if (std::shared_ptr<GameObject> obj = std::dynamic_pointer_cast<GameObject>(SceneOBJ[i]))
		{
			if (player->posY - 1 == obj->posY && player->posX == obj->posX || player->posY + 1 == obj->posY && player->posX == obj->posX || player->posY == obj->posY && player->posX - 1 == obj->posX || player->posY == obj->posY && player->posX + 1 == obj->posX)
			{
				if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					if (portal->is_locked)
					{
						for (short i = 0; i < player->inventory.Container.size(); i++)
						{
							if (std::shared_ptr<Key> _key = std::dynamic_pointer_cast<Key>(player->inventory.Container[i].item))
							{
								if (_key->key_type == portal->key_type)
								{
									player->inventory.DiscardItem(_key, 1, true);
									portal->is_locked = false;
									portal->mirror->is_locked = false;
									has_key = true;
									break;
								}
							}
						}
						if (!has_key)
						{
							scene_log = "[!] This door is locked. Find a key first.";
						}
						else
						{
							scene_log = "[!] The door opened.";
						}
					}
				}	
			}

			else if (player->posX == obj->posX && player->posY == obj->posY)
			{
				if (std::dynamic_pointer_cast<Item>(obj))
				{
					bool removeObject = UI_Interaction.Initialize(player, obj, SceneOBJ);
					
					if (removeObject)
					{
						SceneOBJ.erase(SceneOBJ.begin() + i);
						i--;
						Interaction();
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

				else if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					#pragma region FUNCIONANDO
					chosen_portal = portal;

					// Definindo spawn do player na outra scena;
					player->posX = portal->mirror->posX;
					player->posY = portal->mirror->posY;

					// Passando o player, caso o mesmo seja null para a proxima cena.
					if (chosen_portal->destiny->player == nullptr)
					{
						chosen_portal->destiny->AddObject(player);
					}

					currentScene = false;
					#pragma endregion
				}
			}

		}

		// Movimentação Inimiga
		if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJ[i]))
		{
			enemy->Behaviour(false, SceneOBJ);
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

		if (scene_log != "\0")
		{
			std::cout << "\n";
			std::cout << "\n";
			Renderer::Dialog(scene_log);
		}

		UI_GameInterface.Input(player, SceneOBJ);

		scene_log = "\0";

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
					enemy->Behaviour(false, SceneOBJ);
				}
			}
		}
	}

	chosen_portal->destiny->LoadScene();
}