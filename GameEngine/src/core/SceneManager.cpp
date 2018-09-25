#include "SceneManager.h"
#include "../utils/Debug.h"

std::vector<Scene*> SceneManager::scenes_;
int SceneManager::sceneCount_;
int SceneManager::currentSceneIndex_;
Scene* SceneManager::activeScene_;

void SceneManager::updateCurrentScene() {
	//Debug::print("Engine :: SceneManager :: updateCurrentScene()");
	activeScene_->update();
}

void SceneManager::renderCurrentScene() {
	//Debug::print("Engine :: SceneManager :: renderCurrentScene()");
	activeScene_->render();
}

Scene* SceneManager::getScene(int _sceneBuildIndex) {
	//Return a pointer (not a reference)
	return scenes_.at(_sceneBuildIndex);
}

Scene* SceneManager::getScene(const std::string& _sceneName) {
	//Return a pointer (not a reference)
	for (Scene* scene : scenes_) {
		if (scene->getName() == _sceneName)
			return scene;
	}
	return nullptr;
}

void SceneManager::addScene(Scene* _scene) {
	_scene->sceneIndex_ = sceneCount_;
	scenes_.push_back(_scene);
	sceneCount_++;
}

void SceneManager::loadScene(int _sceneBuildIndex){
	Debug::print("Engine :: SceneManager :: loadScene(" + std::to_string(_sceneBuildIndex) + ")");
	Scene* sceneToLoad_ = getScene(_sceneBuildIndex);
	activeScene_->unload();
	currentSceneIndex_ = sceneToLoad_->getSceneIndex();
	activeScene_ = sceneToLoad_;
	activeScene_->load();
}

void SceneManager::loadScene(std::string _sceneName) {
	loadScene(getScene(_sceneName)->getSceneIndex());
}
