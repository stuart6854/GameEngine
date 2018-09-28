#include "GameEngine.h"

#include <glad/glad.h>

#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../utils/Debug.h"
#include "../utils/Time.h"

Window window_;

bool GameEngine::isValidStart() {
	if (SceneManager::sceneCount() == 0) {
		Debug::print("ENGINE :: No scenes in build!");
		return false;
	}

	return true;
}

bool GameEngine::initialise() {
	if(!isValidStart()) {
		Debug::print("ENGINE :: Valid start conditions not met. Shutting down!");
		return false;
	}
	
	// MUST create window_ before using GLAD
	window_.createWindow("Game Engine", 800, 600, false);
	window_.centreOnScreen();
	window_.showFps(true);

	// load all opengl function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Debug::print("ENGINE :: Failed to initialise GLAD!");
		return false;
	}

	initialised_ = true;
	return true;
}

void GameEngine::start(){
	if(!initialised_) {
		Debug::print("ENGINE :: Cannot start engine without initialising!");
		glfwTerminate();
		return;
	}

	double currentFrame_ = glfwGetTime();
	double lastFrame_ = currentFrame_;
	float deltaTime_ = 0;


	SceneManager::loadScene(0); //Load first scene

	// Render loop
	Debug::print("ENGINE :: Starting engine loop");
	while (!window_.shouldClose()) {
		//Delta Calculation
		currentFrame_ = glfwGetTime();
		deltaTime_ = (currentFrame_ - lastFrame_);
		lastFrame_ = currentFrame_;
		Time::setDeltaTime(deltaTime_);

		// Input

		//Update
		SceneManager::updateCurrentScene(deltaTime_);

		//Rendering
		glClearColor(0.39f, 0.58f, 0.93f, 1.0f); // Cornflour Blue
		glClear(GL_COLOR_BUFFER_BIT);
		SceneManager::renderCurrentScene();

		//Update screen
		window_.update();
	}

	glfwTerminate();
}
