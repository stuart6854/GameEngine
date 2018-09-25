#include "Scene.h"
#include "../utils/Debug.h"

std::string Scene::getName() const {
	return name_;
}

int Scene::getSceneIndex() const {
	return sceneIndex_;
}

void Scene::update() {
	Debug::print("test");
}

void Scene::render() {}

void Scene::load() {
	
}

void Scene::unload() {
	
}

Scene::Scene() {
	name_ = "MyScene";
}
