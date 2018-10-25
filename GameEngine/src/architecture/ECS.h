#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include <cassert>
#include "System.h"
#include <iostream>
struct EntityHandle;

class ECS {

private:
	EntityManager entityManager_;
	ComponentManager componentManager_;
	std::vector<std::unique_ptr<System>> systems_;

public:
	void update();

	EntityHandle createEntity();
	void destroyEntity(EntityHandle _entityHandle);

	template<typename C>
	void addComponent(EntityHandle _entityHandle);

	template<typename C>
	C* getComponent(EntityHandle _entityHandle);

	template<typename S>
	void addSystem();

};

inline void ECS::update() {
	for(auto& system : systems_) {
		system->update(1);
	}
}

inline EntityHandle ECS::createEntity() {
	EntityHandle handle;
	handle.ecs = this;
	handle.entity = entityManager_.createEntity();
	return handle;
}

inline void ECS::destroyEntity(EntityHandle _entityHandle) {
	//TODO: find and remove all of Entities components
	entityManager_.destroyEntity(_entityHandle.entity);
}

template <typename C>
void ECS::addComponent(EntityHandle _entityHandle) {
	Component* comp = componentManager_.addComponent(new C());
	entityManager_.addComponent<C>(_entityHandle.entity, comp);

	for (auto& system : systems_) {
		if (system->entityMatchesSignature(_entityHandle.entity)) {
			system->registerEntity(_entityHandle);
		}
	}
}

template <typename C>
C* ECS::getComponent(EntityHandle _entityHandle) {
	const std::string compName = typeid(C).name();
	const int compId = _entityHandle.entity->getComponentId(compName);
	std::shared_ptr<Component> component = componentManager_.getComponent(compId);

	std::shared_ptr<C> returnComp = std::dynamic_pointer_cast<C>(component);
	return returnComp.get();
}

//TODO: Remove component

template <typename S>
void ECS::addSystem() {
	std::unique_ptr<System> system(new S);
	systems_.push_back(std::move(system));
	//std::cout << "ECS::System Added." << std::endl;
}

