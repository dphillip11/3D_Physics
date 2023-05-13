#pragma once
#include "DataManager.h"

class GameObject;

class Component {
public:
	Component(int ID) : gameObjectID(ID) {}
	//only allow constructors with reference to a game object
	Component() = delete;
	virtual ~Component() {}

	std::unique_ptr<GameObject>& GetGameObject()
	{
		return DM::GameObjects[gameObjectID];
	}

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
protected:
	int gameObjectID{ 0 };
};

