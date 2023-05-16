#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Component.h"
class GameObject {
public:
	GameObject(int id) : id_(id) {}

	int GetID() const { return id_; }

	// Gets a component of type T from the game object
	template<typename T>
	auto GetComponent() const;

	// Updates all components attached to the game object
	void Update(float delta_time);

	// Renders all components attached to the game object
	void Render();

	//adds IDs for type attached, does not create component, use DM::AddComponent()
	void AddComponentID(int type_id);

	//removes IDs for type removed, does not delete component, use DM::RemoveComponent()
	void RemoveComponentID(int type_id);

private:

	int id_;
	std::vector<std::size_t> components_;
};

#endif // GAMEOBJECT_H








