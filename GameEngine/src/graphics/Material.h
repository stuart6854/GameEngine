#pragma once

#include "Color.h"

class Material {

	//TODO: Shaders
	//TODO: Texture(s) - diffuse, normal, etc.
	//TODO: Colors

private:
	std::string shaderProgramName_;
	//Texture* diffuseTexture_;
	Color diffuseColor_;

public:
	Material() {
		diffuseColor_ = Color();
	}

	Color* diffuseColor() { return &diffuseColor_; }

};

