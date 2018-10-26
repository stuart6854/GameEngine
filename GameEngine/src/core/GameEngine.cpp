#include "GameEngine.h"

#include <glad/glad.h>

#include "../src/imgui.h"
#include "../src/imgui_impl_glfw.h"
#include "../src/imgui_impl_opengl3.h"

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
	
	// MUST createEntity window_ before using GLAD
	window_.createWindow("Game Engine", 1280, 720, false);
	window_.centreOnScreen();
	window_.showFps(true);

	// load all opengl function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Debug::print("ENGINE :: Failed to initialise GLAD!");
		return false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;	
	ImGui_ImplGlfw_InitForOpenGL(window_.getGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//ImGui::StyleColorsDark();
	io.Fonts->AddFontDefault();

	initialised_ = true;
	return true;
}

void GameEngine::start(){
	if(!initialised_) {
		Debug::print("ENGINE :: Cannot start engine without initialising!");
		glfwTerminate();
		return;
	}

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	float deltaTime = 0;
	
	SceneManager::loadScene(0); //Load first scene

	bool showDemoWindow_imgui = true;
	bool showSceneManager_imgui = true;

	// Render loop
	Debug::print("ENGINE :: Starting engine loop");
	while (!window_.shouldClose()) {
		//Delta Calculation
		currentFrame = glfwGetTime();
		deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;
		Time::setDeltaTime(deltaTime);

		// Input

		//Update
		SceneManager::updateCurrentScene(deltaTime);

		//AI

		//Physics

		//Rendering

		//ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow(&showDemoWindow_imgui);
		Debug::callDebugRenderFuncs();

		ImGui::Render();

		//Scene
		glfwMakeContextCurrent(window_.getGLFWWindow());
		glClearColor(0.39f, 0.58f, 0.93f, 1.0f); // Cornflour Blue
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window_.getGLFWWindow());
		SceneManager::renderCurrentScene();

		//Update screen
		window_.update();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	window_.destroy();
	glfwTerminate();
}
