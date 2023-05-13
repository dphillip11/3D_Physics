#pragma once

class GameObject;

class Component {
public:
	Component(GameObject* gameobject) : gameObject_(gameobject) {}
	//only allow constructors with reference to a game object
	Component() = delete;
	virtual ~Component() {}

	GameObject* GetGameObject()
	{
		return gameObject_;
	}
	// Define any common functionality required by components
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
protected:
	GameObject* gameObject_{ nullptr };
};

