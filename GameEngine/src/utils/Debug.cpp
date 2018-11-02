#include "Debug.h"
#include "../core/Scene.h"
#include <sstream>

std::vector<std::function<void()>> Debug::debugRenderFuncs_;

int entityComboSelection = 0;

void Debug::callDebugRenderFuncs() {
	for(auto& renderFunc : debugRenderFuncs_) {
		renderFunc();
	}
}

void Debug::print(const std::string& _output) {
	std::cout << _output.c_str() << std::endl;
}

void Debug::checkGlError() {
	GLenum err(glGetError());

	while(err != GL_NO_ERROR) {
		std::string error;

		switch(err) {
			case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
			case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
			case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
			case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		std::cout << "[ERROR] GL_" << error.c_str() << std::endl;
		err = glGetError();
	}
}

void Debug::registerDebugRenderFunc(const std::function<void()>& _renderFunc) {
	debugRenderFuncs_.push_back(_renderFunc);
}

void Debug::glDebugMessageCallback(const GLenum _source, const GLenum _type, GLuint _id, const GLenum _severity, GLsizei _length, const GLchar* _message, const void* _userParam) {
	if(_severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;

	std::stringstream output;
	output << "[OPENGL]";

	//Message Severity
	switch (_severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			output << "[NOTIFICATION]";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			output << "[SEVERITY_LOW]";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			output << "[SEVERITY_MED]";
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			output << "[SEVERITY_HIGH]";
			break;
	}

	//Message Source
	switch(_source) {
		case GL_DEBUG_SOURCE_API:
			output << "[API]";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			output << "[WINDOW_SYSTEM]";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			output << "[SHADER_COMPILER]";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			output << "[THIRD_PARTY]";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			output << "[APPLICATION]";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			output << "[OTHER_SRC]";
			break;
	}

	//Message Type
	switch(_type) {
		case GL_DEBUG_TYPE_ERROR:
			output << "[ERROR]";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			output << "[DEPRECATED_BEHAVIOR]";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			output << "[UNDEFINED_BEHAVIOR]";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			output << "[PORTABILITY]";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			output << "[PERFORMANCE]";
			break;
		case GL_DEBUG_TYPE_MARKER:
			output << "[MARKER]";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			output << "[PUSH_GROUP]";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			output << "[POP_GROUP]";
			break;
		case GL_DEBUG_TYPE_OTHER:
			output << "[OTHER]";
			break;
	}

	output << " " << _message << "\n";
	
	print(output.str());
}
