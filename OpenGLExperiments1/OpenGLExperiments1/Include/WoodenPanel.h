#pragma once
#include "Model.h"

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

