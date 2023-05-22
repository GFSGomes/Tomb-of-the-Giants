#pragma once
#include "Grid.hpp"
#include <iostream>

struct Portal;
struct GameObject;

struct Scene
{
	bool currentScene;

	short gridSizeX;
	short gridSizeY;

	Grid grid;
	std::string scene_log;
	std::shared_ptr<Player> player;

	std::shared_ptr<Portal> Exit;
	std::shared_ptr<GameObject> interactionOBJ;
	std::vector<std::shared_ptr<Portal>> ScenePORTALs;
	std::vector<std::shared_ptr<GameObject>> SceneOBJs;

	Scene(short, short);
	~Scene();

	void AddObject(std::shared_ptr<GameObject>);
	void SpawnObjects();
	void Interaction();
	std::shared_ptr<Portal> LoadScene();
};