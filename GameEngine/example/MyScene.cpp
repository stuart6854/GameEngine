#include "MyScene.h"
#include "../src/architecture/systems/MovementSystem.h"
#include "../src/architecture/components/Transform.h"
#include "../src/architecture/components/Movement.h"

void MyScene::init() {
	ecs.addSystem<MovementSystem>();

	EntityHandle entity = ecs.createEntity();
	entity.addComponent<Transform>();
	entity.addComponent<Movement>();
}

void MyScene::update() {
	ecs.update();
}

void MyScene::render() {
	//ecs.render();
}
