#pragma once

#include "../core/Scene.h"
#include <functional>

class Debug {

public:
	static void callDebugRenderFuncs();

	static void print(const std::string& _output);

	static void registerDebugRenderFunc(const std::function<void()>& _renderFunc);
	
private:
	static std::vector<std::function<void()>> debugRenderFuncs_;

};