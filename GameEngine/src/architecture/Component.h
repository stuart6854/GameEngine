#pragma once

#include "../../IDebugRenderable.h"
#include <vector>
#include <map>

class Component : public IDebugRenderable{

private:
	static std::map<std::string, Component*> factoryMap_;

protected:
	void registerComponentType();

public:
	static std::vector<std::string> knownComponentsList_;

	int familyId_ = -1;
	int id_ = 0;

	Component() {
		registerComponentType();
	}
	virtual ~Component() = default;
	virtual Component* clone() const { return new Component(*this); }

	std::string componentType() const;
	
	int familyId();

	virtual void debugRender() override{ }

	template<typename C>
	static std::string ComponentType();

	template<typename C>
	static int ComponentFamilyID();

	static Component* createFromString(const std::string& _compType);

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

