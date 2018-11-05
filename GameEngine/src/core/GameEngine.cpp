#include "GameEngine.h"

#include <glad/glad.h>

#include "../src/imgui.h"
#include "../src/imgui_impl_glfw.h"
#include "../src/imgui_impl_opengl3.h"

#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../utils/Debug.h"
#include "../utils/Time.h"
#include "../architecture/components/Transform.h"
#include "../architecture/components/Movement.h"
#include "../architecture/components/RenderData.h"
#include "../graphics/ShaderProgram.h"
#include "../architecture/components/Camera.h"
Window window;

bool GameEngine::isValidStart() {
	if (SceneManager::sceneCount() == 0) {
		Debug::print("ENGINE :: No scenes in build!");
		return false;
	}

	return true;
}

bool GameEngine::initialise() {
	if(!isValidStart()) {
		Debug::print("ENGINE::Valid start conditions not met. Shutting down!");
		return false;
	}
	
	// MUST createEntity window_ before using GLAD
	window.createWindow("Game Engine", 1280, 720, false);
	window.centreOnScreen();
	window.showFps(true);
	
	// load all opengl function pointers with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Debug::print("ENGINE::Failed to initialise GLAD!");
		return false;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(Debug::glDebugMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;	
	ImGui_ImplGlfw_InitForOpenGL(window.getGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	//ImGui::StyleColorsDark();
	io.Fonts->AddFontDefault();

	Component::RegisterComponentType<Transform>();
	Component::RegisterComponentType<Movement>();
	Component::RegisterComponentType<RenderData>();
	Component::RegisterComponentType<Camera>();


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
	SceneManager::loadScene(0); //Load first scene

	bool showDemoWindow_imgui = true;

	////OPENGL TEST
	
	std::string shaderName = ShaderProgram::CreateProgram("default_program", "res/shaders/vertex.vert", "res/shaders/fragment.frag");
	ShaderProgram::UseProgram(shaderName);

	// Render loop
	Debug::print("ENGINE::Starting engine loop");
	while (!window.shouldClose()) {
		//Delta Calculation
		currentFrame = glfwGetTime();
		const float deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;
		Time::setDeltaTime(deltaTime);

		// Input

		//Update
		SceneManager::updateCurrentScene();

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

		glfwMakeContextCurrent(window.getGLFWWindow());
		glClearColor(0.39f, 0.58f, 0.93f, 1.0f); // Cornflour Blue
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		SceneManager::renderCurrentScene();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Draw GUI after scene rendering

		//Update screen
		window.update();
	}

	ShaderProgram::DeleteProgram(shaderName);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	window.destroy();
	glfwTerminate();
}
