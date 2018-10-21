#pragma once
#include <string>
#include <vector>
#include "../architecture/EntityManager.h"
#include "../architecture/System.h"
#include "../architecture/ComponentManager.h"
#include "../architecture/ComponentHandle.h"
#include <unordered_map>

class Scene {

public:
	Scene();

	std::string getName() const;
	int getSceneIndex() const;

	EntityManager* getEntityManager() { return &entityManager_; }

	template<typename ComponentType>
	void addCustomComponentManager(ComponentManager<ComponentType>* manager);

	template<typename ComponentType>
	void addComponent(Entity _entity);

	template<typename ComponentType>
	ComponentHandle<ComponentType> getComponent(Entity _entity);

	template<typename ComponentType>
	void removeComponent(Entity _entity);

protected:
	EntityManager entityManager_;

private:
	friend class SceneManager;
	friend class Debug;

	std::string name_;
	int sceneIndex_ = -1;

	std::vector<System*> systems_;
	std::unordered_map<std::string, void*> componentManagers_;

	virtual void init();
	virtual void update();
	virtual void render();

	void load();
	void unload();

	template<typename ComponentType>
	ComponentManager<ComponentType>* getComponentManager();

};

template <typename ComponentType>
void Scene::addCustomComponentManager(ComponentManager<ComponentType>* manager) {
	const std::string compName = typeid(ComponentType).name();
	std::cout << "Comp Name: " << compName;

	componentManagers_[compName] = manager;
}

template <typename ComponentType>
void Scene::addComponent(Entity _entity) {
	ComponentManager<ComponentType>* manager = getComponentManager<ComponentType>();
	manager->addComponent(_entity);
}

template <typename ComponentType>
ComponentHandle<ComponentType> Scene::getComponent(Entity _entity) {
	ComponentManager<ComponentType>* manager = getComponentManager<ComponentType>();
	ComponentType* comp = manager->getComponent(_entity);
	return ComponentHandle<ComponentType>(manager, _entity, comp);
}

template <typename ComponentType>
void Scene::removeComponent(Entity _entity) {
	ComponentManager<ComponentType> manager = getComponentManager<ComponentType>();
	manager.removeComponent(_entity);
}

template <typename ComponentType>
ComponentManager<ComponentType>* Scene::getComponentManager() {
	//TODO: This is a performance hit every time we add/remove a component

	std::string compName = typeid(ComponentType).name();

	if (!componentManagers_[compName])
		componentManagers_[compName] = new ComponentManager<ComponentType>;

	ComponentManager<ComponentType>* mgr = static_cast<ComponentManager<ComponentType>*>(componentManagers_[compName]);

	return mgr;
}

