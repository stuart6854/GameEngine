#pragma once
#include "../architecture/EntityManager.h"
#include <string>

class IDebug {
public:
	virtual ~IDebug() = default;

	virtual std::string getTypeName();
	virtual void debugRenderImgui(Entity _entity);

};

inline std::string IDebug::getTypeName() { return "IDebug"; }

inline void IDebug::debugRenderImgui(Entity _entity) {}
