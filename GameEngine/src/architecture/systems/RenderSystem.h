#pragma once
#include "../System.h"
#include "../components/Transform.h"
#include "../components/RenderData.h"
#include <algorithm>
#include "glad/glad.h"
#include "../../graphics/ShaderProgram.h"

class RenderSystem : public System {
	
	struct meshSortKey {
		inline bool operator() (EntityHandle& entity1, EntityHandle& entity2) {
			const std::string mesh1Id = entity1.getComponent<RenderData>()->mesh_->identifier();
			const std::string mesh2Id = entity2.getComponent<RenderData>()->mesh_->identifier();

			return (mesh1Id < mesh2Id);
		}
	};

public:
	RenderSystem();

	inline void render() override;

};

inline RenderSystem::RenderSystem() : System(0){
	systemSignature_.set(Component::ComponentFamilyID<Transform>());
	systemSignature_.set(Component::ComponentFamilyID<RenderData>());
}

inline void RenderSystem::render() {
	//TODO: Minimize texture changes! Hint: Sort by texture first
	//Operation Speeds(slowest to fastest)
	//	-texture
	//	-vb / ib / source stream.
	//	-materials(?)
	//	-constants and other pipeline flags(cull on / off etc).
	//std::sort(registeredEntities_.begin(), registeredEntities_.end(), meshSortKey());

	std::string currentMeshId;
	for(auto& entity : registeredEntities_) {
		auto* transform = entity.getComponent<Transform>();
		auto* renderData = entity.getComponent<RenderData>();
		auto mesh = renderData->mesh_;
		auto material = entity.getComponent<RenderData>()->material_;

		if(mesh->identifier() != currentMeshId) {
			mesh->prepareRender();
			currentMeshId = mesh->identifier();
		}

		Mat4 model;
		model.translate(transform->x, transform->y, transform->z);
		//Rotate
		//Scale
		
		Mat4 view = Mat4::lookAt(Vec3(0, 0, 3), Vec3(0, 0, 0), Vec3::up);
		Mat4 projection = Mat4::perspective(60, 1280.f / 720.f, 0.1f, 100.0f);
		std::cout << "MVP\n";
		std::cout << model << "\n" << std::endl;
		std::cout << view << "\n" << std::endl;
		std::cout << projection << "\n\n" << std::endl;

		ShaderProgram::UseProgram("default_program");
		ShaderProgram::setUniform("default_program", "model", model);
		ShaderProgram::setUniform("default_program", "view", view);
		ShaderProgram::setUniform("default_program", "projection", projection);

		glDrawElements(GL_TRIANGLES, mesh->indicesCount(), GL_UNSIGNED_INT, nullptr);
		
	}
	
	glBindVertexArray(0);
	glUseProgram(0);
}
