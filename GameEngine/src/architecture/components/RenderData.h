#pragma once
#include "../Component.h"
#include "../../imgui.h"
#include "../../graphics/Mesh.h"
#include "../../graphics/Material.h"

class RenderData : public Component {
	
public:
	Mesh* mesh_;
	Material material_;

	Component* clone() const override {
		return new RenderData(*this);
	}

	void debugRender() override {
		ImGui::Text("Mesh");
		ImGui::Text("Material");
		//TODO: Render Material Controls
	}

};
