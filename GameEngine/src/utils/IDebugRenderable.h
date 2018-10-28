#pragma once

class IDebugRenderable {

public:
	virtual ~IDebugRenderable() = default;

	virtual void debugRender() = 0;

};