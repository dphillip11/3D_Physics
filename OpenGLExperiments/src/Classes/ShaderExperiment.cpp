#include "PCH/pch.h"
#include "ShaderExperiment.h"


ShaderExperiment::ShaderExperiment() : COLUMNS((int)sqrt(BLOCKS)), model(std::make_unique<Model>())
{
	shader = std::make_unique<Shader>("shaders/vertex/drawOblongs.hlsl", "shaders/fragment/drawOblongs.hlsl", "shaders/geometry/drawOblongs.hlsl");

	auto params = new glm::vec3[BLOCKS];

	for (int i = 0;i < BLOCKS; i++)
	{
		params[i] = glm::vec3((float)i, rand() % 10, rand() % 50);
	}
	model->setVertices(params, 3 * BLOCKS, model->_VAO, model->_VBO);
	delete[](params);
	model->setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	shader->setInt("columns", COLUMNS);
}

void ShaderExperiment::draw(Camera camera, float time)
{
	shader->use();
	shader->setFloat("time", time);
	shader->setInt("columns", COLUMNS);
	shader->setMat4("MVP", camera.projection * camera.lookAt());
	shader->setVec3("camPosition", camera._position);
	model->draw();
}
