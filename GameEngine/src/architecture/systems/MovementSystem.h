#pragma once
#include "../System.h"

class MovementSystem : public System {

public:
	MovementSystem();

	void init() override;
	void update(float _deltaTime) override;

};

inline MovementSystem::MovementSystem() {
	//systemSignature_.set(Position::familyId());
	//systemSignature_.set(Velocity::familyId());
}

inline void MovementSystem::init() {}

inline void MovementSystem::update(float _deltaTime) {
	for(auto& entity : registeredEntities_) {
		//TODO: Get Transform Component
		//TODO: Get Velocity Component

		//tranform.position  += movement.velocity * _deltaTime;
		//movement.position  += movement.acceleration * _deltaTime;
	}
}

