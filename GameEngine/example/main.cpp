#include "MyScene.h"
#include <iostream>
#include "../src/core/SceneManager.h"
#include "../src/core/GameEngine.h"
#include "../src/maths/Math.h"
#include "../src/maths/Mat4.h"

int main() {
	//Register Custom Components
	//Component::RegisterComponentType<CustomCompType>();

	MyScene myScene_;
	SceneManager::addScene(&myScene_);

	GameEngine engine_;
	if(!engine_.initialise()) {
		std::cout << "GAME :: Failed to initialise engine!" << std::endl;
		return -1;
	}
	engine_.start();

	std::cout << "Press [ENTER] to exit...";
	std::cin.get();

	return 0;
}
