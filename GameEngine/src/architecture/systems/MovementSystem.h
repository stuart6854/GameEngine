#pragma once
#include "../components/Transform.h"
#include "../components/Movement.h"
#include "../../utils/Time.h"

class MovementSystem : public System {

public:
	MovementSystem();

	inline void update() override;
};

inline MovementSystem::MovementSystem(): System(5) {
	systemSignature_.set(Component::ComponentFamilyID<Transform>());
	systemSignature_.set(Component::ComponentFamilyID<Movement>());
}

inline void MovementSystem::update() {
	for(auto& entityHandle : registeredEntities_) {
		Transform* transform = entityHandle.getComponent<Transform>();
		Movement* movement = entityHandle.getComponent<Movement>();

		transform->x += movement->velX * Time::deltaTime();
		transform->y += movement->velY * Time::deltaTime();
		transform->z += movement->velZ * Time::deltaTime();
	}
}
