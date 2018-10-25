#pragma once
#include <map>
#include "Component.h"
#include "Entity.h"
#include <iostream>
#include "../imgui.h"

class ComponentManager : public IDebug {

public:
	void addComponent(Entity _entity, Component* _component) {
		if (componentName_.empty())
			componentName_ = _component->getTypeName();

		entityMap_.insert(std::pair<unsigned int, Component>(_entity.id, *_component));
		std::cout << "ComponentManager<" << componentName_ << ">::Component added for: " << _entity << std::endl;
	}

	Component* getComponent(Entity _entity) {
		const auto it = entityMap_.find(_entity.id);
		if (it == entityMap_.end())
			return nullptr;

		Component* comp = &(it->second);
		return comp;
	}

	template<typename ComponentType>
	Component* getComponent(Entity _entity) {
		Component* comp = getComponent(_entity);
		auto* outputComp = dynamic_cast<ComponentType*>(comp);
		
		return outputComp;
	}

	void removeComponent(Entity _entity) {
		auto it = entityMap_.find(_entity.id);
		entityMap_.erase(it);
		std::cout << "ComponentManager<" << componentName_ << ">::Component removed for: " << _entity << std::endl;
	}
	
	void debugRenderImgui(Entity _entity) override {
		Component* comp = getComponent(_entity);
		if (comp == nullptr)
			return;
		
		if (ImGui::CollapsingHeader(getTypeName().c_str())) {
			IDebug* renderable = comp;

			renderable->debugRenderImgui(_entity);
		}
	}

	inline std::string getTypeName() override {
		return componentName_;
	};

private:
	std::string componentName_;

	std::map<unsigned int, Component> entityMap_;

};
