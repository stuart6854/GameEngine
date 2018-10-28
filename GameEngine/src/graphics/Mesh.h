#pragma once
#include <vector>
#include "../maths/Vec3.h"
#include "../maths/Vec2.h"

class Mesh {
	
	struct Vertex {
		Vec3 position;
		Vec2 texCoord;
		Vec3 normal;
	};
public:
	std::vector<Vertex> data_;

};
