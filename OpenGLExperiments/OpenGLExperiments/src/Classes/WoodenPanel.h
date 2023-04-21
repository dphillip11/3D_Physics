#pragma once
#include "Model.h"
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "Shader.h"
#include "Texture.h"

class WoodenPanel : public Model
{
public:
	Texture texture;
	Shader* shader;

	WoodenPanel();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
	~WoodenPanel() { }
		//delete(shader); }

};

