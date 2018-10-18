#pragma once

#include <iostream>
#include "../core/Scene.h"

using std::cout;
using std::endl;
using std::string;

class Debug {

public:
	static void print(string output_);

	static void drawSceneManager(bool* show, Scene* _scene);

private:
	//static void drawSceneManager_TreeGameobjectRecursive(Transform* _obj, int* _objCount, const int _selectionMask, int* _nodeClicked);

};

