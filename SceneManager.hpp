#pragma once
#include "Scene.hpp"

struct SceneManager
{
	std::vector<Scene> Scenes;
	std::vector<std::shared_ptr<Scene>> _Scenes;

	SceneManager();
	~SceneManager();

	void StartGame();
};