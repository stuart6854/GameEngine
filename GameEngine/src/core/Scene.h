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
	void addCustomComponentManager(ComponentManager* manager);

	void addComponent(Entity _entity, Component* _component);

	template<typename ComponentType>
	ComponentHandle getComponent(Entity _entity);

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
	std::unordered_map<std::string, ComponentManager*> componentManagers_;

	virtual void init();
	virtual void update();
	virtual void render();

	void load();
	void unload();

	ComponentManager* getComponentManager(const std::string& _componentType);
	
	std::vector<ComponentManager*> getComponentManagers() {
		std::vector<ComponentManager*> managers;
		for(auto& it : componentManagers_) {
			managers.push_back(it.second);
		}

		return managers;
	}

};

template <typename ComponentType>
void Scene::addCustomComponentManager(ComponentManager* manager) {
	const std::string compName = typeid(ComponentType).name();
	std::cout << "Comp Name: " << compName;

	componentManagers_[compName] = manager;
}

inline void Scene::addComponent(Entity _entity, Component* _component) {
	const std::string compType = _component->componentType();
	std::cout << "Scene::AddComponent - " << compType << std::endl;
	ComponentManager* manager = getComponentManager(compType);
	manager->addComponent(_entity, _component);
}

template <typename ComponentType>
ComponentHandle Scene::getComponent(Entity _entity) {
	ComponentManager* manager = getComponentManager();
	ComponentType* comp = manager->getComponent(_entity);
	return ComponentHandle(manager, _entity, comp);
}

template <typename ComponentType>
void Scene::removeComponent(Entity _entity) {
	ComponentManager* manager = getComponentManager(typeid(ComponentType).name());
	manager->removeComponent(_entity);
}

inline ComponentManager* Scene::getComponentManager(const std::string& _componentType) {
	if (!componentManagers_[_componentType])
		componentManagers_[_componentType] = new ComponentManager;

	ComponentManager* mgr = componentManagers_[_componentType];

	return mgr;
}

