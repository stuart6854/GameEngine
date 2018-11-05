#include "ShaderProgram.h"

std::map<std::string, unsigned int> ShaderProgram::shaderPrograms_;

std::string ShaderProgram::CreateProgram(const std::string _programName, const std::string _vertexFile, const std::string _fragmentFile) {
	TextAsset vertexSrc = TextAsset::LoadFile(_vertexFile);
	TextAsset fragmentSrc = TextAsset::LoadFile(_fragmentFile);

	return CreateProgram(_programName, vertexSrc, fragmentSrc);
}

std::string ShaderProgram::CreateProgram(const std::string _programName, TextAsset _vertexSrc, TextAsset _fragmentSrc) {
	if(shaderPrograms_.find(_programName) != shaderPrograms_.end()) {
		Debug::print("ShaderProgram::CreateProgram - Program_Name already exists: " + _programName);
		return "[ERROR]";
	}

	std::string vertSrcStr = _vertexSrc.GetString();
	std::string fragSrcStr = _fragmentSrc.GetString();

	const GLchar* vertSrc = vertSrcStr.c_str();
	const GLchar* fragSrc = fragSrcStr.c_str();

	unsigned int vertId, fragId;
	vertId = glCreateShader(GL_VERTEX_SHADER);
	fragId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertId, 1, &vertSrc, nullptr);
	glCompileShader(vertId);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertId, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertId, 512, nullptr, infoLog);
		Debug::print("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		Debug::print(infoLog);
	}

	glShaderSource(fragId, 1, &fragSrc, nullptr);
	glCompileShader(fragId);
	glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragId, 512, nullptr, infoLog);
		Debug::print("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		Debug::print(infoLog);
	}

	unsigned int programId;
	programId = glCreateProgram();
	glAttachShader(programId, vertId);
	glAttachShader(programId, fragId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(programId, 512, nullptr, infoLog);
		Debug::print(infoLog);
	}

	glDeleteShader(vertId);
	glDeleteShader(fragId);

	shaderPrograms_.insert(std::make_pair(_programName, programId));

	return _programName;
}

void ShaderProgram::UseProgram(const std::string _programName) {
	const unsigned int programId = shaderPrograms_[_programName];

	glUseProgram(programId);
}

void ShaderProgram::DeleteProgram(const std::string _programName) {
	const unsigned int programId = shaderPrograms_[_programName];

	glDeleteProgram(programId);
}

void ShaderProgram::setUniform(std::string _programName, std::string _uniformName, Mat4 _matrix) {
	const auto programId = shaderPrograms_[_programName];
	const auto location = glGetUniformLocation(programId, _uniformName.c_str());
	glUniformMatrix4fv(location, 1, GL_TRUE, &_matrix.m11);
}
