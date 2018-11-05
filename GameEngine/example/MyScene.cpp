#include "MyScene.h"
#include "../src/architecture/systems/MovementSystem.h"
#include "../src/architecture/components/Transform.h"
#include "../src/architecture/components/Movement.h"
#include "../src/architecture/components/RenderData.h"
#include "../src/architecture/systems/RenderSystem.h"
#include "../src/architecture/components/Camera.h"
std::vector<int> indices = {
		0, 1, 2
};

std::vector<float> vertices = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

std::vector<float> normals = {
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f,
	0.f, 0.f, -1.f
};

std::vector<float> texCoords = {
	0.f, 0.f,
	0.f, 0.f,
	0.f, 0.f,
};

EntityHandle entity, camera;

void MyScene::init() {
	ecs.addSystem<MovementSystem>();
	ecs.addSystem<RenderSystem>();

	entity = ecs.createEntity();
	entity.addComponent<Transform>();
	entity.addComponent<Movement>(); 
	entity.addComponent<RenderData>();

	RenderData* renderData = entity.getComponent<RenderData>();
	renderData->mesh_ = Mesh::CreateMesh("triangle", indices, vertices, normals, texCoords);

	camera = ecs.createEntity();
	camera.addComponent<Transform>();
	camera.addComponent<Camera>();

}

void MyScene::update() {
	ecs.update();
}

void MyScene::render() {
	ecs.render();
}
