#include "EntityManager.h"
#include <iostream>

Entity EntityManager::create() {
	Entity e = Entity(++nextId_);
	if (e.id == 0)
		std::cerr << "ERROR::Created Entity with ID=0!" << std::endl;

	aliveEntities_.push_back(e);
	std::cout << "EntityManager::Entity Created: " << e << std::endl;
	return e;
}

void EntityManager::destroy(Entity _e) {
	//TODO: Find and unregister/destroy entities components

	for (auto it = aliveEntities_.begin(); it != aliveEntities_.end(); ++it) {
		if (*it == _e) {
			aliveEntities_.erase(it);
			break;
		}
	}
	std::cout << "EntityManager::Entity Destroyed: " << _e << std::endl;
}
