#include "Debug.h"
#include "../core/Scene.h"
#include <imgui/imgui.h>

void Debug::print(string output_) {
	cout << output_.c_str() << endl;
}

void Debug::drawSceneManager(bool* show, Scene* _scene) {
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Scene Manager")) {
		ImGui::End();
		return;
	}

	ImGui::PushItemWidth(100); // ImGui::InputInt("", &entityId_imgui);
	ImGui::SameLine();
	if (ImGui::Button("New GameObject")) {
		//TODO: Create gameobject
	}
	ImGui::Separator();

	if(ImGui::TreeNode("Scene: _sceneName_")) {
		static int selection_mask = (1 << 2);
		int node_clicked = -1;
		int objCount = -1;
		//TODO: Do below for each gameobject in scene
		//for (auto& gameobject : *_scene->getGameObjects()) {
			//objCount++;
			//drawSceneManager_TreeGameobjectRecursive(gameobject.getComponent<Transform>(), &objCount, selection_mask, &node_clicked);
		//}

		if(node_clicked != -1) {
			selection_mask = (1 << node_clicked);
		}

		ImGui::TreePop();
	}

	ImGui::Separator();

	//TODO: Loop through gameobjects components
	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::Text("Transform Controls");
	}

	if (ImGui::CollapsingHeader("Renderer")) {
		ImGui::Text("Renderer Controls");
	}

	ImGui::End();
}

//void Debug::drawSceneManager_TreeGameobjectRecursive(Transform* _obj, int* _objCount, const int _selectionMask, int* _nodeClicked) {
//	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((_selectionMask & (1 << *_objCount)) ? ImGuiTreeNodeFlags_Selected : 0);
//	bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)_objCount, treeNodeFlags, "_gameObject_");
//	if (ImGui::IsItemClicked()) {
//		_nodeClicked = _objCount;
//	}
//	if (nodeOpen) {
//		//Loop children and call this recursive method with them
//		for (auto& child : *_obj->getChildren()) {
//			_objCount++;
//			drawSceneManager_TreeGameobjectRecursive(&child, _objCount, _selectionMask, _nodeClicked);
//		}
//		ImGui::TreePop();
//	}
//}

