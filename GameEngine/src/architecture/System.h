#pragma once
#include <bitset>
#include <vector>
#include "Entity.h"

class System {

public:
	virtual void init() {}; // Run before update() & render(), but AFTER game initialisation
	virtual void update(float _deltaTime) {};
	virtual void render() {};

	/*void setWorld(World _world) {
		world_ = _world;
	}*/

	void registerEntity(Entity _entity) {
		registeredEntities_.push_back(_entity);
	}

	void deRegisterEntity(Entity _entity) {		
		for (auto it = registeredEntities_.begin(); it != registeredEntities_.end(); ++it) {
			Entity e = *it;
			if(e == _entity) {
				registeredEntities_.erase(it);
				return;
			}
		}
	}

protected:
	std::bitset<64> systemSignature_;

	std::vector<Entity> registeredEntities_;

	//World world_;

};

