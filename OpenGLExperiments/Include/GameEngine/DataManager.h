#include "GameObject.h"
#include "GameEngine/TypeCounter.h"

class DataManager {
public:
	// quick lookup gameobjects
	std::unordered_map<int, std::unique_ptr<GameObject>> GameObjects;

	// quick lookup, gameobject ID, then component type ID
	std::unordered_map<int, std::unordered_map<std::size_t, std::unique_ptr<Component>>> Components;

	template<typename T>
	int GetTypeID() {
		return TypeID<T>::Get();
	}

	template<typename T>
	int GetTypeID(T param) {
		return TypeID<T>::Get();
	}

	static DataManager& getInstance() {
		static DataManager instance;
		return instance;
	}

	int NewGameObject() {
		{
			int id = next_id_;
			GameObjects.emplace(id, std::make_unique<GameObject>(id));
			next_id_++;
			return id;
		}
	}

	void  RemoveGameObject(int id) {
		GameObjects.erase(id);
		Components.erase(id);
	}

	template<typename T, typename... Args>
	T* AddComponent(int object_id, Args&&... args) {
		auto& component_map = Components[object_id];
		auto type_id = GetTypeID<T>();
		auto it = component_map.find(type_id);
		if (it == component_map.end()) {
			component_map.emplace(type_id, std::make_unique<T>(object_id, std::forward<Args>(args)...));
			GameObjects.at(object_id)->AddComponentID(type_id);
		}
		return GetComponent<T>(object_id);
	}


	template<typename T>
	void RemoveComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto type_id = GetTypeID<T>();
		auto it = component_map.find(type_id);
		if (it != component_map.end()) {
			component_map.erase(it);
			GameObjects.at(object_id)->RemoveComponentID(type_id);
		}
	}

	template<typename T>
	T* GetComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto type_id = GetTypeID<T>();
		auto it = component_map.find(type_id);
		if (it == component_map.end()) {
			return nullptr;
		}
		return static_cast<T*>(it->second.get());
	}

	//return GameObjects with attached component type
	template<typename T>
	std::vector<int> FilterObjectsByComponent() {
		std::vector<int> filteredObjects;
		auto typeID = GetTypeID<T>();
		for (const auto& entry : GameObjects) {
			int objectID = entry.first;
			const auto& component_map = Components[objectID];
			if (component_map.find(typeID) != component_map.end()) {
				filteredObjects.push_back(objectID);
			}
		}
		return filteredObjects;
	}

private:
	int next_id_ = 0;

	DataManager() = default;
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
};

#define DM DataManager::getInstance()