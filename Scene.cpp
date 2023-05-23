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
#include "Wall.hpp"
#include "Portal.hpp"

Scene::Scene(short _gridSizeX, short _gridSizeY) : grid{_gridSizeX, _gridSizeY}, scene_log{"\0"}, currentScene{false}, interactionOBJ{nullptr}
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
	// AddObject simplesmente adiciona GameObjects ao vetor SceneOBJ;
	SceneOBJs.push_back(obj);

	if (player == nullptr)
	{
		// Se o player foi adicionado, adiciona também sua FOV:
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

	if (std::shared_ptr<Wall> wall = std::dynamic_pointer_cast<Wall>(obj))
	{
		for (std::shared_ptr<Wall> wallbrick : wall->bricks)
		{
			SceneOBJs.push_back(wallbrick);
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
	bool _hasKey{false};
	bool _removeObject{false};
	char _input{'\0'};

	std::cout << "\n" << "\n";

	if (scene_log != "\0")
	{
		std::cout << " | " << scene_log << "\n";
		scene_log = "\0";
	}

	_input = UI_GameInterface.Input(player, SceneOBJs, 0); // Player Input;

	
	if (interactionOBJ)
	{	
		_removeObject = UI_Interaction.Initialize(player, interactionOBJ, SceneOBJs); // Chamada de Interação;
	}

	for (short i = 0; i < SceneOBJs.size(); i++)
	{
		if (std::shared_ptr<GameObject> obj = std::dynamic_pointer_cast<GameObject>(SceneOBJs[i]))
		{
			if (std::dynamic_pointer_cast<Wall>(obj)) continue; // Ignorando Walls;

			/*** NÃO-INTERAÇÕES ***/
			if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
			{
				if (!enemy->alive)
				{
					SceneOBJs.erase(SceneOBJs.begin() + i);
					interactionOBJ = nullptr;
					scene_log = "\0";
					_input = '\0';
					i--;
					break;
				}
			}
			if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
			{
				
			}
			/*** INTERAÇÕES POR APROXIMAÇÃO ***/
			if (player->posY - 1 == obj->posY && player->posX == obj->posX || player->posY + 1 == obj->posY && player->posX == obj->posX || player->posY == obj->posY && player->posX - 1 == obj->posX || player->posY == obj->posY && player->posX + 1 == obj->posX)
			{
				// Como o inimigo é teletransportado para longe, a interação não o remove de cena:
				if (std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(obj))
				{
					if (!enemy->alive)
					{
						SceneOBJs.erase(SceneOBJs.begin() + i);
						interactionOBJ = nullptr;
						scene_log = "\0";
						i--;
						break;
					}

					if (interactionOBJ == enemy)
					{
						interactionOBJ = nullptr;
						scene_log = "\0";
					}

					if (_input == '\r')
					{
						if (!interactionOBJ)
						{
							scene_log = "[!] " + enemy->name + " spotted!";
							interactionOBJ = enemy;
							_input = '\0';
						}
					}
					else if (player->posX == enemy->lookX && player->posY == enemy->lookY)
					{
						if (!interactionOBJ)
						{
							scene_log = "[!] " + enemy->name + " found you!";
							interactionOBJ = enemy;
						}
						else
						{
							interactionOBJ = nullptr;
							scene_log = "\0";
						}
					}
					
				}
				if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(obj))
				{
					if (_input == '\r')
					{
						if (_removeObject)
						{
							SceneOBJs.erase(SceneOBJs.begin() + i);
							i--;
						}
						interactionOBJ = nullptr;
						scene_log = "\0";
						break;
					}
					else
					{
						if (!interactionOBJ)
						{
							scene_log = "[!] " + item->name + " found!";
							interactionOBJ = item;
						}
						else
						{
							if (interactionOBJ == item)
							{
								interactionOBJ = nullptr;
								scene_log = "\0";
							}
						}
						break;
					}
				}
				if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					if (_input == '\r')
					{
						if (portal->isLocked)
						{
							for (short i = 0; i < player->inventory.Container.size(); i++)
							{
								if (std::shared_ptr<Key> _key = std::dynamic_pointer_cast<Key>(player->inventory.Container[i].item))
								{
									if (_key->keyType == portal->keyType)
									{
										player->inventory.DiscardItem(_key, 1, true);
										i--;
										portal->isLocked = false;
										portal->mirror->isLocked = false;
										_hasKey = true;
									}
								}
							}

							if (!_hasKey)
							{
								if (portal->keyType != KeyType::SECRET_KEY)
								{
									scene_log = "[!] This door is locked.";
								}
								_input = '\0';
							}
							else
							{
								if (portal->keyType == KeyType::SECRET_KEY)
								{
									scene_log = "[!] A secrect chamber was opened.";
								}
								else
								{
									scene_log = "[!] Door was opened.";
								}
								_input = '\0';
							}
						}
					}
					else
					{
						if (portal->keyType == KeyType::SECRET_KEY)
						{
							if (portal->isLocked)
							{
								for (short i = 0; i < player->inventory.Container.size(); i++)
								{
									if (std::shared_ptr<Key> _key = std::dynamic_pointer_cast<Key>(player->inventory.Container[i].item))
									{
										if (_key->keyType == portal->keyType)
										{
											portal->secretReveal = true;
											_hasKey = true;
											scene_log = "[!] You found a secret chamber!";
											_input = '\0';
										}
									}
								}
							}
						}
					}
				}
			}
			
			/*** INTERAÇÕES POR SOBREPOSIÇÃO ***/
			if (player->posX == obj->posX && player->posY == obj->posY)
			{
				if (std::shared_ptr<Portal> portal = std::dynamic_pointer_cast<Portal>(obj))
				{
					if (!portal->isLocked)
					{
						// Definindo spawn do player na próxima scena;
						player->posX = portal->mirror->posX;
						player->posY = portal->mirror->posY;

						Exit = portal;
						currentScene = false;
					}
				}
			}
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

		Interaction(); // Player Input
		

		if (IsPaused)
		{
			continue;
		}
		else
		{
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