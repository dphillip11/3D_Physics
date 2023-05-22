#pragma once
#include "Mesh.h"
#include <unordered_map>
#include <string>

class MeshManager {
public:
	static MeshManager& GetInstance() {
		static MeshManager instance;
		return instance;
	}

	Mesh& LoadMesh(const char* filepath) {
		if (m_Meshes.find(filepath) != m_Meshes.end()) {
			return m_Meshes[filepath];
		}
		std::lock_guard<std::mutex> lock(mesh_load_mutex); // Lock the mutex
		Mesh mesh;
		ParseFile(filepath, mesh);
		m_Meshes[filepath] = mesh;
		return m_Meshes[filepath];
	}

private:
	std::mutex mesh_load_mutex;
	void ParseFile(const char* filepath, Mesh& mesh);
	MeshManager() = default;
	std::unordered_map<std::string, Mesh> m_Meshes;
};