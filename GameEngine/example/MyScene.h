#pragma once
#include "../src/core/Scene.h"

class MyScene : public Scene{

public:
	void init() override;
	void update() override;
	void render() override;

};

