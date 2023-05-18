#include "PCH/pch.h"
#include "GameEngine/GameObject.h"
#include "GameEngine/DataManager.h"
#include "GameEngine/Component.h"

// Gets a component of type T from the game object
template<typename T>
auto GameObject::GetComponent() const { //maybe check vector array first?
	return DM.GetComponent<T>(id_);
}

// Updates all components attached to the game object
void GameObject::Update(float delta_time) {
	for (auto& componentID : components_) {
		DM.Components[id_][componentID]->Update(delta_time);
	}
}

// Renders all components attached to the game object
void GameObject::Render() {

	for (auto& componentID : components_) {
		DM.Components[id_][componentID]->Render();
	}

}

//adds IDs for type attached, does not create component, use DM::AddComponent()
void GameObject::AddComponentID(int type_id) {
	components_.push_back(type_id);
}

//removes IDs for type removed, does not delete component, use DM::RemoveComponent()
void GameObject::RemoveComponentID(int type_id) {
	auto it = std::find(components_.begin(), components_.end(), type_id);
	if (it != components_.end()) {
		components_.erase(it);
	}
}








