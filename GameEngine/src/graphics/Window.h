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
	void setTitle(std::string _title);

	bool shouldClose();


private:
	GLFWwindow* window_;
	std::string title_;
	int width_, height_;
	bool fullscreen_;

	void initialise();

};

