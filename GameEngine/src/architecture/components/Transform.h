#pragma once
#include "../Component.h"
#include "../../maths/Vec3.h"
#include <../src/imgui.h>

class Transform : public Component {

public:
	Vec3 position_;
	//Quaternion rotation_;
	Vec3 scale_ = Vec3(1, 1, 1);

	friend std::ostream& operator<<(std::ostream& _output, Transform& _transform) {
		//_output << "Position(" << _transform.position_ << ")";
		return _output;
	}

private:
	void debugRenderImgui(Entity _entity) override {
		float pos[3] = { position_.x(), position_.y(), position_.z() };
		ImGui::InputFloat3("Position", pos);
		position_.set(pos);

		float rot[3] = {0, 0, 0};// = { position_.x(), position_.y(), position_.z() };
		ImGui::InputFloat3("Rotation", rot);
		//position_.set(pos);

		float scale[3] = { scale_.x(), scale_.y(), scale_.z() };
		ImGui::InputFloat3("Scale", scale);
		scale_.set(scale);
	}

};
