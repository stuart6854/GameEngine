#pragma once

class ComponentManager;

struct ComponentHandle {

	Entity* entity;
	Component* component;
	ComponentManager* mgr;

	ComponentHandle(ComponentManager* _mgr, Entity* _e, Component* _comp) {
		entity = _e;
		mgr = _mgr;
		component = _comp;
	}

	void destroy() {
		mgr->removeComponent(*entity);
	}

};
