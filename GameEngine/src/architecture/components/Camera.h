#pragma once
#include "../Component.h"

class Camera : public Component {

	enum Projection{ Orthographic = 0, Perspective = 1 };

public:
	Projection projection = Projection::Perspective;

	float near_ = 0.1f;
	float far_ = 1000.0f;
	//Orthographic
	float size = 3;

	//Perspective
	float fov = 60.0f;

	Component* clone() const override {
		return new Camera(*this);
	}

	friend std::ostream& operator<<(std::ostream& _output, Camera& _camera) {
		_output << "Camera(" << _camera.projection << ")";
		return _output;
	}

	void debugRender() override {
		int projSelection = projection;
		ImGui::Combo("Projection", &projSelection, "Orthographic\0Perspective");
		projection = static_cast<Projection>(projSelection);

		if(projection == Projection::Orthographic) {
			ImGui::InputFloat("Size", &size);
		}else if(projection == Projection::Perspective) {
			ImGui::InputFloat("Field of View", &fov);
		}
		ImGui::InputFloat("Near", &near_);
		ImGui::InputFloat("Far", &far_);
	}

};

