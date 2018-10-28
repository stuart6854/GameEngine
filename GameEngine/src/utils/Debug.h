#pragma once

#include <functional>
#include <vector>
#include <glad/glad.h>

class Debug {

public:
	static void callDebugRenderFuncs();

	static void print(const std::string& _output);

	static void registerDebugRenderFunc(const std::function<void()>& _renderFunc);
	
private:
	friend class GameEngine;

	static std::vector<std::function<void()>> debugRenderFuncs_;

	static void glDebugMessageCallback(const GLenum _source, const GLenum _type, GLuint _id, const GLenum _severity, GLsizei _length, const GLchar* _message, const void* _userParam);

};
