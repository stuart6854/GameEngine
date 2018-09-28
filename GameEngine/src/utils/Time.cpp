#include "Time.h"

float Time::deltaTime_;
int Time::fps_;

void Time::setDeltaTime(float _dt) {
	deltaTime_ = _dt;
	fps_ = 1.f / deltaTime_;
}

float Time::deltaTime() {
	return deltaTime_;
}

int Time::fps() {
	return fps_;
}
