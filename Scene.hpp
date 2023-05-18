#pragma once
#include "Grid.hpp"
#include <iostream>

struct Portal;
struct GameObject;

struct Scene
{
	Grid grid;
	bool currentScene;
	short gridSizeX;
	short gridSizeY;

	std::string scene_log;
	std::shared_ptr<Player> player;
	std::shared_ptr<Portal> chosen_portal;
	std::vector<std::shared_ptr<GameObject>> SceneOBJ;

	Scene(short, short);
	~Scene();

	void AddObject(std::shared_ptr<GameObject>);
	void SpawnObjects();
	void Interaction();
	void LoadScene();
};