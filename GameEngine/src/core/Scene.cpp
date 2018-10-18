#include "Scene.h"
#include "../utils/Debug.h"

Scene::Scene() {
	name_ = "MyScene";
}

std::string Scene::getName() const {
	return name_;
}

int Scene::getSceneIndex() const {
	return sceneIndex_;
}

void Scene::init() {}

void Scene::update() {}

void Scene::render() {}

void Scene::load() {
	this->init();
}

void Scene::unload() {}
