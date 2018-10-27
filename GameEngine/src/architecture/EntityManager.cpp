#include "EntityManager.h"

int EntityManager::nextId_ = 1;

void EntityManager::addComponent(std::shared_ptr<Entity> _entity, Component* _comp) {
	std::string compType = _comp->componentType();
	_entity->addComponent(compType, _comp);
}

std::shared_ptr<Entity> EntityManager::createEntity() {
	Entity* e = new Entity(nextId_++);
	std::shared_ptr<Entity> entityPtr(e);
	entities.push_back(entityPtr);

	std::cout << "EntityManager::Entity(" << entityPtr->id() << ") created." << std::endl;

	return entities.back();
}

void EntityManager::destroyEntity(std::shared_ptr<Entity> _entity) {
	const auto it = std::find(entities.begin(), entities.end(), _entity);
	entities.erase(it);
	std::cout << "EntityManager::Entity(" << _entity->id() << ") destroyed." << std::endl;
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities() {
	std::vector<std::shared_ptr<Entity>> returnEntities;

	for(auto& entity : entities) {
		returnEntities.push_back(entity);
	}

	return returnEntities;
}
