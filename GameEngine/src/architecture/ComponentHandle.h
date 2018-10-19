#pragma once

template<typename ComponentType>
class ComponentManager;

template<typename ComponentType>
struct ComponentHandle {

	Entity entity;
	ComponentType* component;
	ComponentManager<ComponentType>* mgr;

	ComponentHandle(ComponentManager<ComponentType>* _mgr, Entity _e, ComponentType* _comp) {
		entity = _e;
		mgr = _mgr;
		component = _comp;
	}

	void destroy() {
		mgr->removeComponent(entity);
	}

};
