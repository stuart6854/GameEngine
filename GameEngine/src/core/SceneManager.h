#pragma once
#include <string>
#include <vector>
#include "Scene.h"

class SceneManager{

private:
	static std::vector<Scene*> scenes_;
	static int sceneCount_;
	static int currentSceneIndex_;
	static Scene* activeScene_;

	static void updateCurrentScene();
	static void renderCurrentScene();

	friend class GameEngine;

public:
	static int sceneCount() { return sceneCount_; }

	static Scene* getScene(int _sceneBuildIndex);
	static Scene* getScene(const std::string& _sceneName);

	static void addScene(Scene* _scene);

	static void loadScene(int _sceneBuildIndex);
	static void loadScene(std::string _sceneName);

};

