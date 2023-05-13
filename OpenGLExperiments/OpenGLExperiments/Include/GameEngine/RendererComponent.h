#include "Component.h"

class RendererComponent : public Component {
public:
	RendererComponent(GameObject* gameobject) : Component(gameobject) {};
	virtual ~RendererComponent() {}

	virtual void Update(float deltaTime) = 0;

	virtual void Render() = 0;
};