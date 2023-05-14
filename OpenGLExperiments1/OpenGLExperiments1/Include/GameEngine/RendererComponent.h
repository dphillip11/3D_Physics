#include "Component.h"
#ifndef RENDERERCOMPONENT_H
#define RENDERERCOMPONENT_H

class RendererComponent : public Component {
public:
	RendererComponent(int gameobjectID) : Component(gameobjectID) {};
	virtual ~RendererComponent() {}

	virtual void Update(float deltaTime) = 0;

	virtual void Render() = 0;
};

#endif // RENDERERCOMPONENT_H