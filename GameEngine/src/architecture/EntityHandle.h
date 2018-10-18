#pragma once
#include "../architecture/Entity.h"
#include "../core/Scene.h"
#include "ComponentHandle.h"

struct EntityHandle {

	Entity entity;
	Scene* scene;

	template<typename ComponentType>
	void addComponent(ComponentType _component) {
		scene->addComponent<ComponentType>(entity);
	}

	template<typename ComponentType>
	ComponentHandle<ComponentType> getComponent() {
		return scene->getComponent<ComponentType>(entity);
	}

	template<typename ComponentType>
	void removeComponent() {
		scene->removeComponent<ComponentType>(entity);
	}

};
