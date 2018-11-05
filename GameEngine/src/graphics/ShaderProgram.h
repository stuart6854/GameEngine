#pragma once
#include <map>
#include "../utils/TextAsset.h"
#include "../maths/Mat4.h"

class ShaderProgram {

private:
	static std::map<std::string, unsigned int> shaderPrograms_;

public:
	static std::string CreateProgram(const std::string _programName, const std::string _vertexFile, const std::string _fragmentFile);
	static std::string CreateProgram(const std::string _programName, TextAsset _vertexSrc, TextAsset _fragmentSrc);

	static void UseProgram(const std::string _programName);
	static void DeleteProgram(const std::string _programName);

	static void setUniform(std::string _programName, std::string _uniformName, Mat4 _matrix);

};

