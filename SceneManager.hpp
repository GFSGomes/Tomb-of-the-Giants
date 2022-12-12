#pragma once
#include "Scene.hpp"

struct SceneManager
{
	std::vector<Scene> Scenes;

	SceneManager();
	~SceneManager();
	void StartGame();
};

extern SceneManager sceneManager;