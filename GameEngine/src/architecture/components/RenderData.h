#pragma once
#include "../Component.h"
#include "../../imgui.h"
#include "../../graphics/Mesh.h"
#include "../../graphics/Material.h"

class RenderData : public Component {
	
public:
	std::shared_ptr<Mesh> mesh_;
	Material material_;

	Component* clone() const override {
		return new RenderData(*this);
	}

	void debugRender() override {
		std::string meshId = "Mesh: " + mesh_->identifier();
		ImGui::Text(meshId.c_str());
		ImGui::Text("Material");
		ImGui::Separator();
		//TODO: Render Material Controls
		ImGui::ColorEdit4("Diffuse Color", (float*)material_.diffuseColor(), ImGuiColorEditFlags_NoInputs);

		ImGui::Separator();
	}

};
