#pragma once
#include "Entity.h"
#include <vector>

class EntityManager {

public:
	Entity create();

	void destroy(Entity _e);

private:
	unsigned int nextId_ = 0;

	std::vector<Entity> aliveEntities_;

};

