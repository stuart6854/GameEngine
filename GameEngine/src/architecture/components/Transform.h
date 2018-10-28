#pragma once
#include "../Component.h"
#include <ostream>
#include "../../imgui.h"

class Transform : public Component {

public:
	float x = 0, y = 0, z = 0;

	Component* clone() const override {
		return new Transform(*this);
	}

	friend std::ostream& operator<<(std::ostream& _output, Transform& _transform) {
		_output << "Transform(" << _transform.x << ", " << _transform.y << ", " << _transform.z << ")";
		return _output;
	}

	void debugRender() override {
		float pos[3] = {x, y, z};
		ImGui::InputFloat3("Position(x,y,z)", pos);
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}

};
