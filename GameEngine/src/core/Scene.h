#pragma once
#include <string>

class Scene {

private:
	std::string name_;
	int sceneIndex_ = -1;

	virtual void update();
	virtual void render();

	void load();
	void unload();

	friend  class SceneManager;

public:
	Scene();

	std::string getName() const;
	int getSceneIndex() const;

};
