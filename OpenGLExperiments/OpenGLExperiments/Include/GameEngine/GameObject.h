#pragma once
#include <memory>
#include <vector>
#include "Component.h"
#include  "imgui.h"

class GameObject {
public:
	template<typename T>
	void AddComponent() {
		components_.emplace_back(std::make_unique<T>(this));
	}

	// Removes a component from the game object
	template <typename T>
	void RemoveComponent() {
		for (auto it = components_.begin(); it != components_.end(); ++it) {
			auto t_component = dynamic_cast<T*>(it->get());
			if (t_component) {
				components_.erase(it);
				return;
			}
		}
	}

	// Gets a component of type T from the game object
	template<typename T>
	T* GetComponent() const {
		for (const auto& component : components_) {
			auto t_component = dynamic_cast<T*>(component.get());
			if (t_component) {
				return t_component;
			}
		}
		return nullptr;
	}

	// Updates all components attached to the game object
	void Update(float delta_time) {
		for (auto& component : components_) {
			component->Update(delta_time);
		}
	}

	// Renders all components attached to the game object
	void Render() {
		ImGui::Text("GameObject: ");
		for (auto& component : components_) {
			component->Render();
		}
	}

private:
	std::vector<std::unique_ptr<Component>> components_;
};









