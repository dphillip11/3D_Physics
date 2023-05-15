#include "GameObject.h"
#include "GameEngine/TypeCounter.h"

class DataManager {
public:
	//static DataManager& getInstance();

	// quick lookup gameobjects
	static std::unordered_map<int, std::unique_ptr<GameObject>> GameObjects;

	// quick lookup, gameobject ID, then component type ID
	static std::unordered_map<int, std::unordered_map<std::size_t, std::unique_ptr<Component>>> Components;

	////creates an object and returns its ID
	//int NewGameObject();

	////delete game object and components
	//void RemoveGameObject(int id);

	//// adds a component if none exists, returns reference to component
	//template<typename T>
	//T* AddComponent(int object_id);

	//template<typename T>
	//void RemoveComponent(int object_id);

	//template<typename T>
	//T* GetComponent(int object_id);

	//template<typename T>
	//int GetTypeID();

	//template<typename T>
	//int GetTypeID(T param);
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

	template<typename T>
	T* AddComponent(int object_id) {
		auto& component_map = Components[object_id];
		auto type_id = GetTypeID<T>();
		auto it = component_map.find(type_id);
		if (it == component_map.end()) {
			component_map.emplace(type_id, std::make_unique<T>(object_id));
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

private:
	int next_id_ = 0;

	DataManager() = default;
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
};

#define DM DataManager::getInstance()