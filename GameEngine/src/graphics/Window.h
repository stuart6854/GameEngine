#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class Window{

public:
	void createWindow(std::string _title, int _width, int _height, bool _fullscreen);
	void update();
	void destroy();

	void centreOnScreen();
	void setVisible(bool _visible);
	void setTitle(const std::string& _title);
	void showFps(bool _showFps);

	bool shouldClose();

	GLFWwindow* getGLFWWindow() { return window_; }

private:
	GLFWwindow* window_;
	std::string title_;
	int width_, height_;
	bool fullscreen_ = false;
	bool showFps_ = false;

	void initialise();

};

