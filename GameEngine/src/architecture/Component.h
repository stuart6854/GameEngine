#pragma once

#include "../../IDebugRenderable.h"
#include <vector>

class Component : public IDebugRenderable{

private:
	void registerComponentType();

public:
	static std::vector<std::string> knownComponentsList_;

	int familyId_ = -1;
	int id_ = 0;

	Component() {
		registerComponentType();
	}
	virtual ~Component() = default;

	std::string componentType() const;
	
	int familyId();

	virtual void debugRender() override = 0;

	template<typename C>
	static std::string ComponentType();

	template<typename C>
	static int ComponentFamilyID();

};


template<typename C>
std::string Component::ComponentType() {
	std::string compType = typeid(C).name();
	const std::string toRemove = "class ";
	const int start = compType.find(toRemove);
	compType = compType.erase(start, toRemove.size());
	return compType;
}

template<typename C>
int Component::ComponentFamilyID() {
	int index = 0;
	for(const auto& it : knownComponentsList_) {
		if(it == ComponentType<C>()) {
			return index;
		}
		index++;
	}

	knownComponentsList_.push_back(ComponentType<C>());

	return index;
}

