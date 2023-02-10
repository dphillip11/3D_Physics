#include "WoodenPanel.h"
#include "../Libraries/glm/glm/matrix.hpp"
#include "../Libraries/glm/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/glm/gtc/type_ptr.hpp"


WoodenPanel::WoodenPanel()
{
	shader = new Shader("src/shaders/vertex/container.hlsl", "src/shaders/fragment/container.hlsl");
	float vertices[12] = {
		0.5,0.5,0, 
		-0.5,-0.5,0, 
		0.5,-0.5,0,
		-0.5,0.5,0
	};
	int indices[6] = {
		0,3,1, 1,0,2
	};
	setVertices(vertices, 12);
	setIndices(indices, 6);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	texture.setParameters();
	texture.loadImage("src/Textures/container.jpg");
}


void WoodenPanel::shadedDraw(GLenum fillMode, GLenum drawMode)
{
	shader->use();
	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	draw(fillMode, drawMode);
}

