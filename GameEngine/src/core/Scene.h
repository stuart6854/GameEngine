#pragma once
#include <string>
#include <vector>
#include "../architecture/EntityManager.h"
#include "../architecture/System.h"
#include "../architecture/ComponentManager.h"
#include "../architecture/ComponentHandle.h"

class Scene {

public:
	Scene();

	std::string getName() const;
	int getSceneIndex() const;

	template<typename ComponentType>
	void addCustomComponentManager(ComponentManager<ComponentType>* manager);

	template<typename ComponentType>
	void addComponent(Entity _entity);

	template<typename ComponentType>
	ComponentHandle<ComponentType> getComponent(Entity _entity);

	template<typename ComponentType>
	void removeComponent(Entity _entity);

private:
	std::string name_;
	int sceneIndex_ = -1;

	EntityManager entityManager_;
	std::vector<System> systems_;
	std::vector<void*> componentManagers_;

	virtual void init();
	virtual void update();
	virtual void render();

	void load();
	void unload();

	template<typename ComponentType>
	ComponentManager<ComponentType>* getComponentManager();

	friend class SceneManager;

};

template <typename ComponentType>
void Scene::addCustomComponentManager(ComponentManager<ComponentType>* manager) {
	const int familyId = GetComponentFamily<ComponentType>();
	if (familyId >= componentManagers_.size())
		componentManagers_.resize(familyId + 1);

	componentManagers_[familyId] = manager;
}

template <typename ComponentType>
void Scene::addComponent(Entity _entity) {
	ComponentManager<ComponentType> manager = getComponentManager<ComponentType>();
	manager.addComponent(_entity);
}

template <typename ComponentType>
ComponentHandle<ComponentType> Scene::getComponent(Entity _entity) {
	ComponentManager<ComponentType> manager = getComponentManager<ComponentType>();
	return manager.getComponent(_entity);
}

template <typename ComponentType>
void Scene::removeComponent(Entity _entity) {
	ComponentManager<ComponentType> manager = getComponentManager<ComponentType>();
	manager.removeComponent(_entity);
}

template <typename ComponentType>
ComponentManager<ComponentType>* Scene::getComponentManager() {
	//TODO: This is a performance hit every time we add/remove a component

	int familyId = GetComponentFamily<ComponentType>();
	if (familyId >= componentManagers_.size())
		componentManagers_.resize(familyId + 1);

	if (!componentManagers_[familyId])
		componentManagers_[familyId] = new ComponentManager<ComponentType>;

	return static_cast<ComponentManager<ComponentType>*>(componentManagers_[familyId]);
}

