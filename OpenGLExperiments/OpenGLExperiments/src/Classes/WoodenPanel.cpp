#include "WoodenPanel.h"
#include <glm/glm/matrix.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


WoodenPanel::WoodenPanel()
{
	shader = new Shader("shaders/vertex/container.hlsl", "shaders/fragment/container.hlsl");
	float vertices[12] = {
		0.5,0.5,0, 
		-0.5,-0.5,0, 
		0.5,-0.5,0,
		-0.5,0.5,0
	};
	int indices[6] = {
		0,3,1, 1,0,2
	};
	setVertices(vertices, 12, _VAO, _VBO);
	setIndices(indices, 6, _EBO);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	texture.setParameters();
	texture.loadImage("Textures/container.jpg");
}


void WoodenPanel::shadedDraw(GLenum fillMode, GLenum drawMode)
{
	shader->use();
	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	draw(fillMode, drawMode);
}
