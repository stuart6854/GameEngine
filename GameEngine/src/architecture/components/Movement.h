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
};
