#include "Debug.h"
#include "../core/Scene.h"
#include "../maths/Math.h"
#include <../src/imgui.h>
#include <sstream>
#include <algorithm>

int entityComboSelection = 0;

void Debug::print(string _output) {
	cout << _output.c_str() << endl;
}

void Debug::drawSceneManager(bool* show, Scene* _scene) {
	//std::vector<Entity> entities = _scene->getEntityManager()->getEntities();
	std::vector<const char*> entityItems;
	/*for(auto& entity : entities) {
		std::ostringstream oss;
		oss << entity;
		const std::string item = oss.str();
		char* itemChar = new char[item.length() + 1];
		std::copy(item.c_str(), item.c_str() + item.length() + 1, itemChar);
		entityItems.push_back(itemChar);
	}*/

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Scene Manager")) {
		ImGui::End();
		return;
	}

	//entityComboSelection = Math::clamp(entityComboSelection, -1, entities.size() - 1);
	//ImGui::PushItemWidth(200); ImGui::Combo("", &entityComboSelection, entityItems.data(), entities.size());

	ImGui::SameLine();
	if (ImGui::Button("New Entity")) {
		//TODO: Create Entity
		//_scene->getEntityManager()->create();
	}

	if (entityComboSelection == -1) {
		ImGui::End();
		return;
	}

	//const Entity selectedEntity = entities.at(entityComboSelection);

	ImGui::SameLine();
	if (ImGui::Button("Destroy Entity")) {
		//TODO: Destroy Entity
		//_scene->getEntityManager()->destroy(selectedEntity);
	}
	ImGui::Separator();

	//Get Components for selected entity
	/*std::vector<ComponentManager*> componentManagers = _scene->getComponentManagers();
	for(auto& manager : componentManagers) {
		auto* renderable = static_cast<IDebug*>(manager);
		if (renderable)
			renderable->debugRenderImgui(selectedEntity);
	}*/

	ImGui::Separator();

	//static ImGuiTextFilter filter;
	//filter.Draw("Component Filter");
	//for (auto& manager : componentManagers) {
	//	auto* compManager = static_cast<ComponentManager*>(manager);
	//	auto* debug = static_cast<IDebug*>(manager);

	//	std::string compName = compManager->getTypeName();
	//	if (compManager && filter.PassFilter(compName.c_str())) {

	//		std::string buttonLbl = "Add " + compName;
	//		if(ImGui::Button(buttonLbl.c_str())) {
	//			std::cout << "Adding component: " << compName << endl;
	//			//compManager->addComponent(selectedEntity); //TODO: BROKEN. FIX ME!
	//			
	//		}
	//	}

	//}

	ImGui::End();
}

