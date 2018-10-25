#pragma once
#include <vcruntime_typeinfo.h>
#include <vector>

template<typename T>
static std::string ComponentType() {
	std::string compType = typeid(T).name();
	const std::string toRemove = "class ";
	const int start = compType.find(toRemove);
	compType = compType.erase(start, toRemove.size());
	return compType;
}

static std::vector<std::string> knownComponentsList_;

template<typename T>
static int GetComponentFamilyID() {
	int index = 0;
	for (const auto& it : knownComponentsList_) {
		if (it == ComponentType<T>()) {
			return index;
		}
		index++;
	}

	knownComponentsList_.push_back(ComponentType<T>());

	return index;
}

class Component {

public:
	int familyId_ = -1;
	int id_;

	virtual ~Component() = default;

	std::string componentType() const;
	
	int familyId() {
		if (familyId_ >= 0)
			return familyId();

		int index = 0;
		for (const auto& it : knownComponentsList_) {
			if (it == componentType()) {
				return index;
			}
			index++;
		}

		knownComponentsList_.push_back(componentType());
		familyId_ = index;

		return familyId_;
	}

};

inline std::string Component::componentType() const {
	std::string compType = typeid(*this).name();
	const std::string toRemove = "class ";
	const int start = compType.find(toRemove);
	compType = compType.erase(start, toRemove.size());
	return compType;
}
