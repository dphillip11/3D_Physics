#include "PCH/pch.h"
#include "GameEngine/DataManager.h"
//#include "GameEngine/TypeCounter.h"

int TypeIDCounter::counter_ = 0;

std::unordered_map<int, std::unique_ptr<GameObject>> DataManager::GameObjects;

// quick lookup, gameobject ID, then component type ID
std::unordered_map<int, std::unordered_map<std::size_t, std::unique_ptr<Component>>> DataManager::Components;

//template<typename T>
//int DataManager::GetTypeID() {
//	return TypeID<T>::Get();
//}
//
//template<typename T>
//int DataManager::GetTypeID(T param) {
//	return TypeID<T>::Get();
//}
//
//DataManager& DataManager::getInstance() {
//	static DataManager instance;
//	return instance;
//}
//
//int DataManager::NewGameObject() {
//	{
//		int id = next_id_;
//		GameObjects.emplace(id, std::make_unique<GameObject>(id));
//		next_id_++;
//		return id;
//	}
//}
//
//void  DataManager::RemoveGameObject(int id) {
//	GameObjects.erase(id);
//	Components.erase(id);
//}
//
//template<typename T>
//T* DataManager::AddComponent(int object_id) {
//	auto& component_map = Components[object_id];
//	auto type_id = GetTypeID<T>();
//	auto it = component_map.find(type_id);
//	if (it == component_map.end()) {
//		component_map.emplace(type_id, std::make_unique<T>(object_id));
//		GameObjects[object_id]->AddComponentID(type_id);
//	}
//	return GetComponent<T>(object_id);
//}
//
//
//template<typename T>
//void DataManager::RemoveComponent(int object_id) {
//	auto& component_map = Components[object_id];
//	auto type_id = GetTypeID<T>();
//	auto it = component_map.find(type_id);
//	if (it != component_map.end()) {
//		component_map.erase(it);
//		GameObjects[object_id]->RemoveComponentID(type_id);
//	}
//}
//
//template<typename T>
//T* DataManager::GetComponent(int object_id) {
//	auto& component_map = Components[object_id];
//	auto type_id = GetTypeID<T>();
//	auto it = component_map.find(type_id);
//	if (it == component_map.end()) {
//		return nullptr;
//	}
//	return static_cast<T*>(it->second.get());
//}


