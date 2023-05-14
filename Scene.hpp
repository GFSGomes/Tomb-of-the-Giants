#pragma once
#include "Grid.hpp"

struct Scene
{
	Grid grid;
	bool currentScene;
	short gridSizeX;
	short gridSizeY;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<GameObject>> SceneOBJ;

	Scene(short, short);
	~Scene();

	void AddObject(std::shared_ptr<GameObject>);
	void SpawnObjects();
	void Interaction();
	void LoadScene();
};