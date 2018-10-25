#pragma once
#include "../Component.h"
#include <ostream>

class Transform : public Component {

public:
	float x = 0, y = 0, z = 0;

	friend std::ostream& operator<<(std::ostream& _output, Transform& _transform) {
		_output << "Transform(" << _transform.x << ", " << _transform.y << ", " << _transform.z << ")";
		return _output;
	}

};
