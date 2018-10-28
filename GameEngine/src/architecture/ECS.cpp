#include "ECS.h"

#include "../imgui.h"
#include <sstream>
#include "../utils/Debug.h"
#include "../maths/Math.h"
#include "../utils/IDebugRenderable.h"

ECS::ECS() {
	Debug::registerDebugRenderFunc([=]() {
		this->renderDebugEntityManager();
	});
}

void ECS::update() {
	for(auto& system : systems_) {
		system->update();
	}
}

void ECS::render() {
	for(auto& system : systems_) {
		system->render();
	}
}


EntityHandle ECS::createEntity() {
	EntityHandle handle;
	handle.ecs = this;
	handle.entity = entityManager_.createEntity();
	return handle;
}

void ECS::destroyEntity(EntityHandle _entityHandle) {
	//TODO: find and remove all of Entities components
	entityManager_.destroyEntity(_entityHandle.entity);
}

//TODO: Remove component

void ECS::addComponent(std::shared_ptr<Entity> _entity, Component* _comp) {
	Component* comp = componentManager_.addComponent(_comp);
	entityManager_.addComponent(_entity, comp);

	EntityHandle eHandle;
	eHandle.entity = _entity;
	eHandle.ecs = this;

	for(auto& system : systems_) {
		if(system->entityMatchesSignature(eHandle.entity)) {
			system->registerEntity(eHandle);
		}
	}
}

void ECS::renderDebugEntityManager() {
	std::vector<std::shared_ptr<Entity>> entities = entityManager_.getEntities();
	std::vector<const char*> entityItems;
	for(auto& entity : entities) {
		std::ostringstream oss;
		oss << "Entity(" << entity->id() << ")";
		const std::string item = oss.str();
		char* itemChar = new char[item.length() + 1];
		std::copy(item.c_str(), item.c_str() + item.length() + 1, itemChar);
		entityItems.push_back(itemChar);
	}

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if(!ImGui::Begin("Scene Manager")) {
		ImGui::End();
		return;
	}

	debug_entitySelection = Math::clamp(debug_entitySelection, -1, entities.size() - 1);
	ImGui::PushItemWidth(200); ImGui::Combo("", &debug_entitySelection, entityItems.data(), entities.size());

	ImGui::SameLine();
	if(ImGui::Button("New Entity")) {
		createEntity();
	}

	if(debug_entitySelection == -1) {
		ImGui::End();
		return;
	}
	const std::shared_ptr<Entity> selectedEntity = entities.at(debug_entitySelection);

	ImGui::SameLine();
	if(ImGui::Button("Destroy Entity")) {
		entityManager_.destroyEntity(selectedEntity);
	}
	ImGui::Separator();

	//Get Components for selected entity
	std::unordered_map<std::string, int> entityCompIdsMap = selectedEntity->getComponentIdsMap(); 
	for(auto& compPair : entityCompIdsMap) {
		std::shared_ptr<Component> component = componentManager_.getComponent(compPair.second);
		if(ImGui::CollapsingHeader(compPair.first.c_str())) {
			auto* debugComp = static_cast<IDebugRenderable*>(component.get());
			debugComp->debugRender();
		}
	}

	ImGui::Separator();

	static ImGuiTextFilter filter;
	filter.Draw("Component Filter");
	for (auto& componentType : Component::knownComponentsList_) {
		if (filter.PassFilter(componentType.c_str())) {

			std::string buttonLbl = "Add " + componentType;
			if(ImGui::Button(buttonLbl.c_str())) {
				//std::cout << "Adding component: " << componentType << std::endl;
				Component* createdComp = Component::createFromString(componentType);
				addComponent(selectedEntity, createdComp);
			}
		}

	}

	ImGui::End();
}
