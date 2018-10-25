#pragma once
#include "../utils/IDebug.h"
#include "Entity.h"

class Component : public IDebug{

public:
	virtual std::string componentType() const { return "Component"; };

	void debugRenderImgui(Entity _entity) override{};

};