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

	WoodenBox();

	void CreateVertices();
	void setUniforms(Camera camera);
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

