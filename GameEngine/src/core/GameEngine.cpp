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
	glDebugMessageCallback(Debug::glDebugMessageCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	
	std::string vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()	{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";
	auto temp = vertexShaderSrc.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &temp, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	std::string fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
void main(){
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} )";
	auto temp2 = fragmentShaderSrc.c_str();

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &temp2, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/*glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	std::cout << infoLog << std::endl;*/

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	////

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
		//SceneManager::updateCurrentScene();

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Draw GUI after scene rendering

		//Update screen
		window.update();
	}

	glDeleteProgram(shaderProgram);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	window.destroy();
	glfwTerminate();
}
