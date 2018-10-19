#pragma once
#include <map>
#include "Component.h"
#include "Entity.h"
#include <iostream>
#include "ComponentHandle.h"
#include "imgui/imgui.h"

template<typename ComponentType>
class ComponentManager : public IDebug {

public:
	void addComponent(Entity _entity) {
		//entityMap_.insert(std::pair<unsigned int, ComponentType>(_entity.id, ComponentType()));
		std::cout << "ComponentManager" << typeid(ComponentType).name() << "::Component added for: " << _entity << std::endl;
	}

	ComponentType* getComponent(Entity _entity) {
		auto it = entityMap_.find(_entity.id);
		if (it == entityMap_.end())
			return nullptr;

		Component<ComponentType>* comp = &(it->second);
		auto* outputComp = dynamic_cast<ComponentType*>(comp);

		//std::cout << "ComponentManager<" << typeid(ComponentType).name() << ">::Got component for: " << _entity << std::endl;
		return outputComp;
	}

	void removeComponent(Entity _entity) {
		auto it = entityMap_.find(_entity.id);
		entityMap_.erase(it);
		std::cout << "ComponentManager" << typeid(ComponentType).name() << "::Component removed for: " << _entity << std::endl;
	}
	
	void debugRenderImgui(Entity _entity) override {
		Component<ComponentType>* comp = getComponent(_entity);
		if (comp == nullptr)
			return;
		
		if (ImGui::CollapsingHeader(getTypeName().c_str())) {
			IDebug* renderable = comp;

			renderable->debugRenderImgui(_entity);
		}
	}

	inline std::string getTypeName() override {
		std::string toErase = "class ";
		std::string compName = typeid(ComponentType).name();
		size_t pos = compName.find(toErase);
		if (pos != std::string::npos)
			compName.erase(pos, toErase.length());
		return compName;
	};

private:
	std::map<unsigned int, ComponentType> entityMap_;

};
