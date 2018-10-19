#pragma once
#include <type_traits>
#include "../utils/IDebug.h"
#include "Entity.h"

struct ComponentCounter {
	static int familyCounter;
};


template<typename ComponentType>
class Component : public IDebug{
public:
	static int familyId();

	void debugRenderImgui(Entity _entity) override = 0;

};

template<typename ComponentType>
int Component<ComponentType>::familyId() {
	static int familyId = ComponentCounter::familyCounter++;
	return familyId;
}

template<typename C>
static int GetComponentFamily() {
	return Component<typename std::remove_const<C>::type>::familyId();
}