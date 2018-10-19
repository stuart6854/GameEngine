#include "MyScene.h"
#include "../src/architecture/components/Transform.h"

void MyScene::init() {
	Entity e = entityManager_.create();
	addComponent<Transform>(e);
	entityManager_.create();
	entityManager_.create();
	entityManager_.create();
	entityManager_.create();
}

void MyScene::update() {

}

void MyScene::render() {
	
}
