#pragma once
#include <bitset>
#include "EntityManager.h"
#include "EntityHandle.h"

class System {

public:
	System(const int _priority) : priority_(_priority){ }
	virtual ~System() = default;

	virtual void update();
	virtual void render();

	void registerEntity(EntityHandle _entityHandle);
	void deRegisterEntity(EntityHandle _entityHandle);

	bool entityMatchesSignature(std::shared_ptr<Entity> _entity);

	bool operator<(const System& _other) const;

private:
	const int priority_;

protected:
	std::bitset<64> systemSignature_;
	std::vector<EntityHandle> registeredEntities_;

};

inline void System::update() {
	
}

inline void System::render() {
	
}

inline void System::registerEntity(EntityHandle _entityHandle) {
	registeredEntities_.push_back(_entityHandle);	
}

inline void System::deRegisterEntity(EntityHandle _entityHandle) {
	for(auto it = registeredEntities_.begin(); it != registeredEntities_.end(); ++it) {
		Entity e = *it->entity;
		if(e == *_entityHandle.entity) {
			registeredEntities_.erase(it);
			return;
		}
	}
}

inline bool System::entityMatchesSignature(std::shared_ptr<Entity> _entity) {
	return (systemSignature_ & _entity->getComponentSignature()) == systemSignature_;
}

inline bool System::operator<(const System& _other) const {
	return this->priority_ < _other.priority_;
}
