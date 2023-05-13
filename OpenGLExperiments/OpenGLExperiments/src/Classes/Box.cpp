#pragma once
#include "pch.h"
#include "Box.h"


Box::Box() {

	//left
	positions.push_back(glm::vec3(-0.5, 0, 0));
	rotations.push_back(glm::vec3(0, 1, 0));
	//right
	positions.push_back(glm::vec3(0.5, 0, 0));
	rotations.push_back(glm::vec3(0, 1, 0));
	//top
	positions.push_back(glm::vec3(0, 0.5, 0));
	rotations.push_back(glm::vec3(1, 0, 0));
	//bottom
	positions.push_back(glm::vec3(0, -0.5, 0));
	rotations.push_back(glm::vec3(1, 0, 0));
	//front
	positions.push_back(glm::vec3(0, 0, 0.5));
	rotations.push_back(glm::vec3(0, 0, 0));
	//back
	positions.push_back(glm::vec3(0, 0, -0.5));
	rotations.push_back(glm::vec3(0, 0, 0));
}

void Box::draw(glm::mat4& view, glm::mat4& projection)
{
	//setup shader
	panel.shader->use();
	glActiveTexture(GL_TEXTURE0);
	panel.texture.bind();
	panel.shader->setMat4("view", view);
	panel.shader->setMat4("projection", projection);


	//calculate instance specific model
	for (int i = 0; i < 6; i++)
	{
		glm::mat4 rotate = glm::mat4(1);
		glm::mat4 translate = glm::translate(glm::mat4(1), positions[i]);
		if (i < 4)
			rotate = glm::rotate(glm::mat4(1), glm::radians(90.0f), rotations[i]);
		glm::mat4 model = _transform * translate * rotate;
		panel.shader->setMat4("model", model);
		panel.draw();
	}

}

void Box::transform(glm::mat4& transformation)
{
	_transform = _transform * transformation;
}

void Box::createBoxTransforms(int n)
{
	for (int i = 0; i < n; i++)
	{
		boxTransforms.push_back(glm::translate(glm::mat4(1), glm::vec3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5)));
		boxTransformations.push_back(glm::rotate(glm::mat4(1), glm::radians((float)(rand() % 10) / 1000), glm::vec3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5)));
	}
}

void Box::drawBoxes(glm::mat4& view, glm::mat4& projection)
{
	//setup shader
	panel.shader->use();
	glActiveTexture(GL_TEXTURE0);
	panel.texture.bind();
	panel.shader->setMat4("view", view);
	panel.shader->setMat4("projection", projection);

	for (int j = 0; j < boxTransforms.size(); j++)
	{
		//calculate instance specific model
		for (int i = 0; i < 6; i++)
		{
			glm::mat4 rotate = glm::mat4(1);
			glm::mat4 translate = glm::translate(glm::mat4(1), positions[i]);
			if (i < 4)
				rotate = glm::rotate(glm::mat4(1), glm::radians(90.0f), rotations[i]);
			boxTransforms[j] = boxTransformations[j] * boxTransforms[j] * boxTransformations[j];
			glm::mat4 model = boxTransforms[j] * translate * rotate;
			panel.shader->setMat4("model", model);
			panel.draw();
		}
	}

}
