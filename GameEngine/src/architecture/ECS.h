#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "System.h"
struct EntityHandle;

class ECS {

private:
	EntityManager entityManager_;
	ComponentManager componentManager_;
	std::vector<std::unique_ptr<System>> systems_;

	int debug_entitySelection = -1;

	void addComponent(std::shared_ptr<Entity> _entity, Component* _comp);

	void renderDebugEntityManager();

public:
	ECS();

	void update();
	void render();

	EntityHandle createEntity();
	void destroyEntity(EntityHandle _entityHandle);

	template<typename C>
	void addComponent(EntityHandle _entityHandle);

	template<typename C>
	C* getComponent(EntityHandle _entityHandle);

	template<typename S>
	void addSystem();

};

template <typename C>
void ECS::addComponent(EntityHandle _entityHandle) {
	addComponent(_entityHandle.entity, new C());
}

template <typename C>
C* ECS::getComponent(EntityHandle _entityHandle) {
	const std::string compName = Component::ComponentType<C>();
	const int compId = _entityHandle.entity->getComponentId(compName);
	std::shared_ptr<Component> component = componentManager_.getComponent(compId);

	std::shared_ptr<C> returnComp = std::dynamic_pointer_cast<C>(component);
	return returnComp.get();
}

template <typename S>
void ECS::addSystem() {
	std::unique_ptr<System> system(new S);
	systems_.push_back(std::move(system));
	//std::cout << "ECS::System Added." << std::endl;
}