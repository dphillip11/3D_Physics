#include "pch.h"
#include "GameObject.h"
#include "DataManager.h"
#include "Component.h"

// Gets a component of type T from the game object
template<typename T>
auto GameObject::GetComponent() const {
	return DM::GetComponent<T>(id_);
}

// Updates all components attached to the game object
void GameObject::Update(float delta_time) {
	for (auto& componentID : components_) {
		DM::Components[id_][componentID]->Update(delta_time);
	}
}

// Renders all components attached to the game object
void GameObject::Render() {
	ImGui::Text("GameObject: ");
	for (auto& componentID : components_) {
		DM::Components[id_][componentID]->Render();
	}
}

//adds IDs for type attached, does not create component, use DM::AddComponent()
template<typename T>
void GameObject::AddComponentID(std::size_t type_id) {
	components_.push_back(type_id);
}

//removes IDs for type removed, does not delete component, use DM::RemoveComponent()
template<typename T>
void GameObject::RemoveComponentID(std::size_t type_id) {
	auto it = std::find(components_.begin(), components_.end(), type_id);
	if (it != components_.end()) {
		components_.erase(it);
	}
}








