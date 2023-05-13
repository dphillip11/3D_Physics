#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "CubeRenderer.h"
#include "MeshComponent.h"
#include "RendererComponent.h"
#include "ShaderComponent.h"
#include <unordered_map>


namespace DataManager {
	int next_id_ = 0;

	//maps for quick lookup
	std::unordered_map<int, std::unique_ptr<GameObject>> GameObjects;
	std::unordered_map<int, std::unique_ptr<TransformComponent>> TransformComponents;
	std::unordered_map<int, std::unique_ptr<CubeRenderer>> CubeRenderers;
	std::unordered_map<int, std::unique_ptr<MeshComponent>> MeshComponents;
	std::unordered_map<int, std::unique_ptr<RendererComponent>> RenderersComponents;
	std::unordered_map<int, std::unique_ptr<ShaderComponent>> ShaderComponents;

	int NewGameObject()
	{
		int id = next_id_;
		GameObjects.emplace(id, std::make_unique<GameObject>());
		next_id_++;
		return id;
	}

	// Function to add a component to the specified map
	template<typename T>
	bool addComponent(int id, std::unordered_map<int, std::unique_ptr<T>>& componentMap)
	{
		// Check if the ID already exists in the map
		if (componentMap.find(id) != componentMap.end())
		{
			return false;
		}

		// Add the new component to the map
		componentMap.emplace(id, std::make_unique<T>());
		return true;
	}
}

namespace DM = DataManager;