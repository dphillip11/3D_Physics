#include "PCH/pch.h"
#include "GameEngine/MeshComponent.h"
#include "GameEngine/MeshManager.h"


MeshComponent::MeshComponent(int gameobjectID, const char* filepath) : Component(gameobjectID), m_mesh(MeshManager::GetInstance().LoadMesh(filepath)) {}


