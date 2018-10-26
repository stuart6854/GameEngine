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

void Debug::registerDebugRenderFunc(const std::function<void()>& _renderFunc) {
	debugRenderFuncs_.push_back(_renderFunc);
}
