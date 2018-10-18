#pragma once

struct ComponentCounter {
	static int counter;
};

template<typename ComponentType>
class Component{

	virtual ~Component();

	static int familyId();

};

template <typename ComponentType>
Component<ComponentType>::~Component() = default;

template <typename ComponentType>
int Component<ComponentType>::familyId() {
	static int familyId = ComponentCounter::counter++;
	return familyId;
}

template<typename C>
static int GetComponentFamily() {
	return Component<typename std::remove_const<C>::type>::familyId();
}

