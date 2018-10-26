#pragma once
#include "../Component.h"
#include <ostream>

class Movement : public Component {

public:
	float velX = 0, velY = 0, velZ = 0;

	friend std::ostream& operator<<(std::ostream& _output, Movement& _movement) {
		_output << "Movement(" << _movement.velX << ", " << _movement.velY << ", " << _movement.velZ << ")";
		return _output;
	}

	void debugRender() override {
		float vel[3] = {velX, velY, velZ};
		ImGui::InputFloat3("Velocity(x,y,z)", vel);
		velX = vel[0];
		velY = vel[1];
		velZ = vel[2];
	}

};
