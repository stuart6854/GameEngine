#pragma once
#include "../src/core/Scene.h"

class MyScene : public Scene{

public:
	void init();
	void update();
	void render() override;

};

