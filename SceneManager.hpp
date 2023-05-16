#pragma once
#include <vector>
#include <memory>

struct Scene;

struct SceneManager
{
	std::vector<Scene> Scenes;
	std::vector<std::shared_ptr<Scene>> _Scenes;

	SceneManager();
	~SceneManager();

	void StartGame();
};