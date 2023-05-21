#include "Scene.hpp"
#include "GameInterfaceUI.hpp"
#include "InteractionUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Light.hpp"
#include "Slot.hpp"
#include "Global.hpp"
#include "Renderer.hpp"
#include <conio.h>
#include <windows.h>
#include "Wall.hpp"
#include "Portal.hpp"

Scene::Scene(short _gridSizeX, short _gridSizeY) : grid{_gridSizeX, _gridSizeY}, asign_log{true}, scene_log{"\0"}, currentScene{false}, player_idle{false}
{
	// +1 é necessário para que a Grid gerada tenha o tamanho literal definido;
	gridSizeX = _gridSizeX + 1;
	gridSizeY = _gridSizeY + 1;
}

Scene::~Scene()
{

}

void Scene::AddObject(std::shared_ptr<GameObject> obj)
{
	SceneOBJs.push_back(obj);

	if (player == nullptr)
	{
		if (std::dynamic_pointer_cast<Player>(obj))
		{
			player = std::dynamic_pointer_cast<Player>(obj);

			if (player == obj)
			{
				for (std::shared_ptr<Light> light : player->FOV)
				{
					SceneOBJs.push_back(light);
				}
			}
		}
	}
	if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
	{
		ScenePORTALs.push_back(portal);
	}
}

void Scene::SpawnObjects()
{
	for (std::shared_ptr<GameObject> obj : SceneOBJs)
	{
		// 1. Foi definida coordenada (posX:-1, posY:-1) em GameObject;
		// 2. Então, tudo que receber uma posição específica após sua criação,
		//	  será posicionado adequadamente. 

		if (obj->posX != -1 && obj->posY != -1)
		{
			obj->SpawnAt(obj->posX, obj->posY);
		}
		else
		{
			obj->SpawnRandom();

			// Prevenindo sobreposição durante o spawn;
			for (std::shared_ptr<GameObject> other : SceneOBJs)
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

	for (short i = 0; i < SceneOBJs.size(); i++)
	{
		if (std::shared_ptr<GameObject> obj = std::dynamic_pointer_cast<GameObject>(SceneOBJs[i]))
		{
			// Proximidade
			if (player->posY - 1 == obj->posY && player->posX == obj->posX || player->posY + 1 == obj->posY && player->posX == obj->posX || player->posY == obj->posY && player->posX - 1 == obj->posX || player->posY == obj->posY && player->posX + 1 == obj->posX)
			{
				if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					if (portal->isLocked)
					{
						for (short i = 0; i < player->inventory.Container.size(); i++)
						{
							if (std::shared_ptr<Key> _key = std::dynamic_pointer_cast<Key>(player->inventory.Container[i].item))
							{
								if (_key->keyType == portal->keyType)
								{
									if (portal->keyType == KeyType::SECRET_KEY)
									{
										grid.secret_portal_reveal = true;
									}

									player->inventory.DiscardItem(_key, 1, true);
									i--;
									portal->isLocked = false;
									portal->mirror->isLocked = false;
									has_key = true;
									break;
								}
							}
						}
						if (!has_key)
						{
							if(portal->keyType == KeyType::SECRET_KEY)
							{
								return;
							}
							
							if (asign_log)
							{
								scene_log = "[!] This door is locked. Find a key first.";
							}
						}
						else
						{
							if (asign_log)
							{
								if (portal->keyType == KeyType::SECRET_KEY)
								{
									scene_log = "[!] A secrect chamber was opened.";
									asign_log = !asign_log;
								}
								else
								{
									scene_log = "[!] The door opened.";
									asign_log = !asign_log;
								}
							}
						}

						asign_log = true;
					}
				}
			}

			// Pontual
			else if (player->posX == obj->posX && player->posY == obj->posY)
			{
				if (std::dynamic_pointer_cast<Item>(obj))
				{
					bool removeObject = UI_Interaction.Initialize(player, obj, SceneOBJs);
					
					if (removeObject)
					{
						SceneOBJs.erase(SceneOBJs.begin() + i);
						i--;
						Interaction();
					}
				}

				else if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
				{
					if (enemy->alive)
					{
						UI_Interaction.Initialize(player, enemy, SceneOBJs);
						
						if (!enemy->alive)
						{
							SceneOBJs.erase(SceneOBJs.begin() + i);
						}
					}
				}

				else if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					asign_log = !asign_log;

					if (!portal->isLocked)
					{	
						#pragma region FUNCIONANDO

						// Definindo spawn do player na outra scena;
						player->posX = portal->mirror->posX;
						player->posY = portal->mirror->posY;

						// Passando o player, caso o mesmo seja null para a proxima cena.

						Exit = portal;
						currentScene = false;
						#pragma endregion
					}
				}
			}

		}

		// Movimentação Inimiga
		if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJs[i]))
		{
			enemy->Behaviour(false, SceneOBJs);
		}
	}
}

std::shared_ptr<Portal> Scene::LoadScene()
{
	GridSizeX = gridSizeX;
	GridSizeY = gridSizeY;

	srand(time(0));

	Exit = nullptr;

	currentScene = true;

	SpawnObjects();

	while (currentScene)
	{
		if (GameOver){
			currentScene = false;
			return Exit;
		}

		UI_GameInterface.Initialize(player);

		grid.UpdateGrid(SceneOBJs, player);

		if (scene_log != "\0" && !player_idle)
		{
			std::cout << "\n\n";
			Renderer::Dialog(scene_log, 5);
		}

		player_idle = UI_GameInterface.Input(player, SceneOBJs);
		
		scene_log = "\0";

		if (IsPaused)
		{
			continue;
		}
		else
		{
			Interaction();

			for (short i = 0; i < SceneOBJs.size(); i++)
			{
				if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(SceneOBJs[i]))
				{
					enemy->Behaviour(false, SceneOBJs);
				}
			}
		}
	}

	return Exit;
}