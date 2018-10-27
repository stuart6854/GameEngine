#include "Component.h"
#include <vector>
#include <vcruntime_typeinfo.h>
#include <iostream>
std::vector<std::string> Component::knownComponentsList_; 
std::map<std::string, Component*> Component::factoryMap_;

void Component::registerComponentType() {
	const std::string compType = componentType();
	if(compType == "Component")
		return;

	const auto it = std::find(knownComponentsList_.begin(), knownComponentsList_.end(), compType);
	if(it == knownComponentsList_.end())
		knownComponentsList_.push_back(compType);

	const auto it2 = factoryMap_.find(compType);
	if(it2 == factoryMap_.end())
		factoryMap_.insert(std::make_pair(compType, (*this).clone()));
}

std::string Component::componentType() const {
	std::string compType = typeid(*this).name();
	const std::string toRemove = "class ";
	const int start = compType.find(toRemove);
	compType = compType.erase(start, toRemove.size());
	return compType;
}

int Component::familyId() {
	if(familyId_ >= 0)
		return familyId();

	int index = 0;
	for(const auto& it : knownComponentsList_) {
		if(it == componentType()) {
			return index;
		}
		index++;
	}

	knownComponentsList_.push_back(componentType());
	familyId_ = index;

	return familyId_;
}

Component* Component::createFromString(const std::string& _compType) {
	auto it = factoryMap_.find(_compType);
	if(it == factoryMap_.end())
		return nullptr;
	Component* comp = &(*it->second->clone());
	return comp;
}
