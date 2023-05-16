#include "Component.h"
#ifndef RENDERERCOMPONENT_H
#define RENDERERCOMPONENT_H

class RendererComponent : public Component {
public:
	RendererComponent(int gameobjectID) : Component(gameobjectID) {};
	virtual ~RendererComponent() {}

	virtual void Update(float deltaTime) {};

	virtual void Render() override;
};

#endif // RENDERERCOMPONENT_H