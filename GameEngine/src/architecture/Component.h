#pragma once
#include "../utils/IDebug.h"
#include "Entity.h"

struct ComponentCounter {
	static int familyCounter;
};


class Component : public IDebug{
public:
	static int familyId();

	void debugRenderImgui(Entity _entity) override = 0;

};

int Component::familyId() {
	static int familyId = ComponentCounter::familyCounter++;
	return familyId;
}

static int GetComponentFamily() {
	return Component::familyId();
}