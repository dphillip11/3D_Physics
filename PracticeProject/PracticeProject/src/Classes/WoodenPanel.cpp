#include "WoodenPanel.h"
#include <glm/glm/matrix.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


WoodenPanel::WoodenPanel()
{
	shader = new Shader("src/shaders/vertex/container.hlsl", "src/shaders/fragment/container.hlsl");
	float vertices[12] = {
		1,1,0, 
		-1,-1,0, 
		1,-1,0,
		-1,1,0
	};
	int indices[6] = {
		0,3,1, 1,0,2
	};
	setVertices(vertices, 12);
	setIndices(indices, 6);
	setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	scale = glm::vec3(1, 1, 1);
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	texture.setParameters();
	texture.loadImage("src/Textures/container.jpg");
}


void WoodenPanel::shadedDraw(GLenum fillMode, GLenum drawMode)
{
	shader->use();
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, position);
	trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, scale);
	unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	draw(fillMode, drawMode);
}