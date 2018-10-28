#pragma once
#include "../System.h"
#include "../components/Transform.h"
#include "../components/RenderData.h"

class RenderSystem : public System {

public:
	RenderSystem();

	inline void render() override;

};

inline RenderSystem::RenderSystem() : System(0){
	systemSignature_.set(Component::ComponentFamilyID<Transform>());
	systemSignature_.set(Component::ComponentFamilyID<RenderData>());
}

inline void RenderSystem::render() {
	
}
