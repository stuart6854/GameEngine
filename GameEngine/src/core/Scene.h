#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../architecture/ECS.h"

class Scene {

public:
	Scene();

	std::string getName() const;
	int getSceneIndex() const;

protected:
	ECS ecs;

private:
	friend class SceneManager;
	friend class Debug;

	std::string name_;
	int sceneIndex_ = -1;

	virtual void init();
	virtual void update();
	virtual void render();

	void load();
	void unload();

};

