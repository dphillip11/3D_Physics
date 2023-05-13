#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include  "imgui.h"

class GameObject {
public:

	int GetID() const { return id_; }

	template<typename T>
	void AddComponent() {
		DM::AddComponent<T>(id_);
	}

	// Removes a component from the game object
	template <typename T>
	void RemoveComponent() {
		DM::RemoveComponent<T>(id_);
	}

	// Gets a component of type T from the game object
	template<typename T>
	T* GetComponent() const {
		return DM::GetComponent<T>(id_);
	}

	// Updates all components attached to the game object
	void Update(float delta_time) {
		for (auto& component : DM::GameObjects[id_]->components_) {
			component->Update(delta_time);
		}
	}

	// Renders all components attached to the game object
	void Render() {
		ImGui::Text("GameObject: ");
		for (auto& component : DM::GameObjects[id_]->components_) {
			component->Render();
		}
	}
private:
	int id_;
};








