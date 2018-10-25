#pragma once
#include <unordered_map>
#include <bitset>
#include <iostream>
#include "Component.h"

class Entity {
private:
	int id_;
	std::unordered_map<std::string, int> components_;
	std::bitset<64> signature_;

public:
	Entity(const int _id) : id_(_id) { }

	int id() {
		return id_;
	}

	std::bitset<64> getComponentSignature() {
		return signature_;
	}

	int getComponentId(const std::string _compType) {
		return components_[_compType];
	}

	void addComponent(const std::string _compType, Component* _comp) {
		components_[_compType] = _comp->id_;
		signature_.set(_comp->familyId());
	}

	bool operator==(const Entity& other) {
		return (this->id() == other.id_);
	}

};

class EntityManager {

private:
	static int nextId_;

	std::vector<Entity> entities;

public:
	Entity* createEntity();

	template<typename C>
	void addComponent(Entity* _entity, Component* _comp);

	void destroyEntity(Entity* e);

};

inline Entity* EntityManager::createEntity() {
	Entity e(nextId_++);

	entities.push_back(e);

	std::cout << "EntityManager::Entity(" << e.id() << ") created." << std::endl;

	return &entities.back();
}

template <typename C>
void EntityManager::addComponent(Entity* _entity, Component* _comp) {
	std::string compType = typeid(C).name();
	_entity->addComponent(compType, _comp);
}

inline void EntityManager::destroyEntity(Entity* e) {
	const auto it = std::find(entities.begin(), entities.end(), *e);
	entities.erase(it);
}
