#include "../GameEngine/src/core/GameEngine.h"
#include "MyScene.h"
#include "core/SceneManager.h"
#include <iostream>

int main() {
	MyScene myScene_;
	SceneManager::addScene(&myScene_);

	GameEngine engine_;
	if(!engine_.initialise()) {
		std::cout << "GAME :: Failed to initialise engine!" << std::endl;
		return -1;
	}
	engine_.start();

	return 0;
}
