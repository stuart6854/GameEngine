#pragma once
#include <map>
#include <memory>
#include "Component.h"

class ComponentManager {

private:
	static int nextId_;
	
	std::map<int, std::shared_ptr<Component>> components;

public:
	~ComponentManager();

	std::shared_ptr<Component> getComponent(const int _id);
	Component* addComponent(Component* _comp);

};

inline ComponentManager::~ComponentManager() {
	/*for(auto& [key, val] : components) {
		delete &val;
	}*/
}

inline std::shared_ptr<Component> ComponentManager::getComponent(const int _id) {
	return components[_id];
}

inline Component* ComponentManager::addComponent(Component* _comp) {
	const int compId = nextId_++;
	_comp->id_ = compId;
	components.insert(std::make_pair(compId, _comp));

	return _comp;
}


