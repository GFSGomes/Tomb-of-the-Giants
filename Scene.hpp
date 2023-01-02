#pragma once
#include "Grid.hpp"
#include "Database.hpp"

struct Scene
{
	bool currentScene;
	Grid grid;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<GameObject>> SceneOBJ;

	Scene(short, short);
	~Scene();

	void AddObject(std::shared_ptr<GameObject>);
	void SpawnObjects();
	void Interaction();
	void LoadScene();
};