#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	Component(int ID) : gameObjectID(ID) {}
	//only allow constructors with reference to a game object
	Component() = delete;
	virtual ~Component() {}

	int GetGameObjectID()
	{
		return gameObjectID;
	}

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
protected:
	int gameObjectID{ 0 };
};

#define ComponentIDString(x) (x + std::to_string(gameObjectID)).c_str()

#endif // COMPONENT_H

