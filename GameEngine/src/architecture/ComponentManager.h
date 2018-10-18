#pragma once
#include <map>
#include "Component.h"
#include "Entity.h"
#include "ComponentHandle.h"
#include <iostream>

template<typename ComponentType>
class ComponentManager {

public:
	void addComponent(Entity _entity) {
		entityMap_.insert(std::pair<unsigned int, ComponentType>(_entity.id, ComponentType()));
		std::cout << "ComponentManager" << typeid(ComponentType).name() << "::Component added for: " << _entity << std::endl;
	}

	ComponentHandle<ComponentType> getComponent(Entity _entity) {
		auto it = entityMap_.find(_entity.id);
		Component<ComponentType>* comp = &(it->second);
		ComponentType* outputComp = dynamic_cast<ComponentType*>(comp);
		ComponentHandle<ComponentType> handle(this, _entity);

		std::cout << "ComponentManager" << typeid(ComponentType).name() << "::Got component for: " << _entity << std::endl;
		return handle;
	}

	void removeComponent(Entity _entity) {
		auto it = entityMap_.find(_entity.id);
		entityMap_.erase(it);
		std::cout << "ComponentManager" << typeid(ComponentType).name() << "::Component removed for: " << _entity << std::endl;
	}

private:
	std::map<unsigned int, ComponentType> entityMap_;

};
