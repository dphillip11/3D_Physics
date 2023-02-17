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
		shader = std::make_unique<Shader>("src/shaders/vertex/woodenBox.hlsl", "src/shaders/fragment/woodenBox.hlsl");
		diffuseMap = Texture();
		diffuseMap.setParameters();
		diffuseMap.loadImage("src/Textures/container2.png", GL_RGBA);
		specularMap = Texture();
		specularMap.setParameters();
		specularMap.loadImage("src/Textures/container2_specular.png", GL_RGBA);
		emissionMap = Texture();
		emissionMap.setParameters();
		emissionMap.loadImage("src/Textures/matrix.jpg", GL_RGB);
	}

	void CreateVertices();
	void setUniforms(Camera camera);
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

