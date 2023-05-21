#include "PCH/pch.h"
#include "GameEngine/MeshManager.h"
#include "obj.h"

void MeshManager::ParseFile(const char* filepath, Mesh& mesh) {
	obj mesh_data;
	mesh_data.read(filepath);
	mesh_data.vertices = mesh_data.unravelIndices(mesh_data.vertices, mesh_data.vertexIndices);
	mesh_data.normalMap = mesh_data.unravelIndices(mesh_data.normalMap, mesh_data.normalIndices);
	mesh_data.textureMap = mesh_data.unravelIndices(mesh_data.textureMap, mesh_data.textureIndices);
	mesh.upper_bounds = mesh_data.upper_bounds;
	mesh.lower_bounds = mesh_data.lower_bounds;

	//vertices
	glBindVertexArray(mesh._VAO);
	mesh.setVertices(&mesh_data.vertices[0], (int)mesh_data.vertices.size() * 3, mesh._VAO, mesh._VBO);
	mesh.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

	//normals
	if (mesh_data.normalMap.size() > 0)
	{
		mesh.setVertices(&mesh_data.normalMap[0], (int)mesh_data.normalMap.size() * 3, mesh._VAO, mesh._VBOnormal);
		mesh.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	}

	//texturemap
	if (mesh_data.textureMap.size() > 0)
	{
		mesh.setVertices(&mesh_data.textureMap[0], (int)mesh_data.textureMap.size() * 3, mesh._VAO, mesh._VBOtexture);
		mesh.setAttributes(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	}

}