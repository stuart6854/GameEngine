#pragma once
#include <ostream>

class Entity {

public:
	Entity(const int _id) : id(_id){}

	unsigned int id; // There should NEVER be an entity with an id of 0

	friend std::ostream& operator<<(std::ostream& _output, Entity& _entity) {
		_output << "Entity(" << _entity.id << ")";
		return _output;
	}

	bool operator==(const Entity& _other) {
		return (id == _other.id);
	}

private:

};

