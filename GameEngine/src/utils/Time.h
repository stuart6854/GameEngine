#pragma once
class Time {

private:
	static float deltaTime_;
	static int fps_;

	static void setDeltaTime(float _dt);

	friend class GameEngine;

public:
	static float deltaTime();
	static int fps();

};

