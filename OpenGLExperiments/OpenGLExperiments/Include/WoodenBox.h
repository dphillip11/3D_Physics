#pragma once
#include <memory>
#include "Model.h"
#include "Texture.h"
#include "Camera.h"

class WoodenBox: public Model
{
public:
	Texture diffuseMap;
	Texture specularMap;
	Texture emissionMap;
	glm::mat4 transform = glm::mat4(1);

	WoodenBox()
	{
		CreateVertices();
		shader = std::make_unique<Shader>("shaders/vertex/woodenBox.hlsl", "shaders/fragment/woodenBox.hlsl");
		diffuseMap = Texture();
		diffuseMap.setParameters();
		diffuseMap.loadImage("Textures/container2.png", GL_RGBA);
		specularMap = Texture();
		specularMap.setParameters();
		specularMap.loadImage("Textures/container2_specular.png", GL_RGBA);
		emissionMap = Texture();
		emissionMap.setParameters();
		emissionMap.loadImage("Textures/matrix.jpg", GL_RGB);
	}

	void CreateVertices();
	void setUniforms(Camera camera);
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

