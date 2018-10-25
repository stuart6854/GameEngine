#pragma once
#include "EntityManager.h"

class ECS;

struct EntityHandle {
	
	Entity* entity;
	ECS* ecs;

	template<typename C>
	void addComponent() {
		ecs->addComponent<C>(*this);
	}

	template<typename C>
	C* getComponent() {
		return ecs->getComponent<C>(*this);
	}

};
