#include "Window.h"
#include "../utils/Time.h"
#include <string>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *_window);

void Window::initialise() {
	// Initialise and configure GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS X
}

void Window::createWindow(std::string _title, int _width, int _height, bool _fullscreen) {
	title_ = _title;
	width_ = _width;
	height_ = _height;
	fullscreen_ = _fullscreen;

	initialise();

	if(window_ != nullptr) {
		std::cout << "Window has already been created" << std::endl;
		return;
	}

	window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
	if (window_ == nullptr) {
		std::cout << "Failed to create GLFW window_" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);

}

void Window::update() {
	// Check and call events and swap buffers
	if (showFps_) glfwSetWindowTitle(window_, (title_ + " | " + std::to_string(Time::deltaTime()) + "ms" + " | " + std::to_string(Time::fps()) + "fps").c_str());
	glfwSwapBuffers(window_);
	glfwPollEvents();
}

void Window::destroy() {}

void Window::centreOnScreen() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowPos(window_, (mode->width / 2) - (width_ / 2), (mode->height / 2) - (height_ / 2));
}

void Window::setVisible(bool _visible) {
	if (_visible) glfwShowWindow(window_);
	else glfwHideWindow(window_);
}

void Window::setTitle(const std::string& _title) {
	title_ = _title;
	glfwSetWindowTitle(window_, _title.c_str());
}

void Window::showFps(const bool _showFps) {
	showFps_ = _showFps;
	setTitle(title_);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window_);
}

void framebufferSizeCallback(GLFWwindow* _window, int _width, int _height) {
	glViewport(0, 0, _width, _height);
}

void processInput(GLFWwindow *_window) {
	/*if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window_, true);*/
}
