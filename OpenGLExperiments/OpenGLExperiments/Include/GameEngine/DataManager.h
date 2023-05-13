#pragma once
#include "GameObject.h"

class TypeIDCounter {
public:
	template<typename T>
	static std::size_t GetID() {
		static std::size_t id = counter_++;
		return id;
	}
private:
	static std::size_t counter_;
};

std::size_t TypeIDCounter::counter_ = 0;

template<typename T>
class TypeID {
public:
	static std::size_t Get() {
		return TypeIDCounter::GetID<T>();
	}
};

namespace DataManager {

	int next_id_ = 0;

	// quick lookup gameobjects
	std::unordered_map<int, std::unique_ptr<GameObject>> GameObjects;

	// quick lookup, gameobject ID, then component type ID
	std::unordered_map<int, std::unordered_map<std::size_t, std::unique_ptr<Component>>> Components;

	//creates an object and returns its ID
	int NewGameObject()
	{
		int id = next_id_;
		GameObjects.emplace(id, std::make_unique<GameObject>(id));
		next_id_++;
		return id;
	}

	//delete game object and components
	void RemoveGameObject(int id)
	{
		GameObjects.erase(id);
		Components.erase(id);
	}

	// adds a component if none exists, returns reference to component
	template<typename T>
	auto AddComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto it = component_map.find(TypeID<T>::Get());
		if (it == component_map.end()) {
			component_map.emplace(TypeID<T>::Get(), std::make_unique<T>());
			std::size_t typeId = TypeID<T>::Get();
			//GameObjects[object_id]->AddComponentID(typeId);
		}
		return GetComponent<T>(object_id);
	}


	template<typename T>
	void RemoveComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto it = component_map.find(TypeID<T>::Get());
		if (it != component_map.end()) {
			component_map.erase(it);
			GameObjects[object_id]->RemoveComponentID(TypeID<T>::Get());
		}
	}

	template<typename T>
	T* GetComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto it = component_map.find(TypeID<T>::Get());
		if (it == component_map.end()) {
			return nullptr;
		}
		return dynamic_cast<T*>(it->second.get());
	}

}

namespace DM = DataManager;