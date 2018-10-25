#pragma once
#include "../components/Transform.h"
#include "../components/Movement.h"
#include <iostream>

class MovementSystem : public System {

public:
	MovementSystem();

	inline void update(float _deltaTime) override;
};

inline MovementSystem::MovementSystem(): System(5) {
	systemSignature_.set(GetComponentFamilyID<Transform>());
	systemSignature_.set(GetComponentFamilyID<Movement>());
}

inline void MovementSystem::update(float _deltaTime) {
	for(auto& entityHandle : registeredEntities_) {
		Transform* transform = entityHandle.getComponent<Transform>();
		Movement* movement = entityHandle.getComponent<Movement>();

		transform->x += movement->velX;
		transform->y += movement->velY;
		transform->z += movement->velZ;
	}
}
