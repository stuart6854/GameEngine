#pragma once
#include "../Component.h"
#include <ostream>

class Position : public Component<Position> {

public:
	float x, y, z;

	friend std::ostream& operator<<(std::ostream& _output, Position& _position) {
		_output << "Position(" << _position.x << ", " << _position.y << ", " << _position.z << ")";
		return _output;
	}

};

