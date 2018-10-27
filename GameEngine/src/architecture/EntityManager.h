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

	std::unordered_map<std::string, int> getComponentIdsMap() {
		return components_;
	}

	bool operator==(Entity& other) {
		return (this->id() == other.id_);
	}

};

class EntityManager {

private:
	static int nextId_;

	std::vector<std::shared_ptr<Entity>> entities;

public:
	std::shared_ptr<Entity> createEntity();

	void addComponent(std::shared_ptr<Entity>, Component* _comp);

	void destroyEntity(std::shared_ptr<Entity> e);

	std::vector<std::shared_ptr<Entity>> getEntities();

};

