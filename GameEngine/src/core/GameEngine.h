#pragma once

class GameEngine {
	
private:
	bool initialised_ = false;
	bool isValidStart();

public:
	bool initialise();
	void start();

};
