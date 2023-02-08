#include "Box.h"
#include <glm/glm/vec3.hpp>
#include <glm/glm/ext/matrix_transform.hpp>

Box::Box() {
	for (int i = 0; i < 6; i++)
	{
		panels.push_back(WoodenPanel());
	}
	//left
	panels[0].transform = glm::translate(panels[0].transform, glm::vec3(-0.5, 0, 0));
	panels[0].transform = glm::rotate(panels[0].transform, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//right
	panels[1].transform = glm::translate(panels[1].transform, glm::vec3(0.5, 0, 0));
	panels[1].transform = glm::rotate(panels[1].transform, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//top
	panels[2].transform = glm::translate(panels[2].transform, glm::vec3(0, 0.5, 0.0));
	panels[2].transform = glm::rotate(panels[2].transform, glm::radians(90.0f), glm::vec3(1, 0, 0));	
	//bottom
	panels[3].transform = glm::translate(panels[3].transform, glm::vec3(0, -0.5, 0));
	panels[3].transform = glm::rotate(panels[3].transform, glm::radians(90.0f), glm::vec3(1, 0, 0));	
	//front
	panels[4].transform = glm::translate(panels[4].transform, glm::vec3(0, 0, 0.5));
	//back
	panels[5].transform = glm::translate(panels[5].transform, glm::vec3(0, 0, -0.5));
}

void Box::draw(glm::mat4& view, glm::mat4& projection)
{
	for (WoodenPanel panel : panels)
	{
		panel.shader->use();
		panel.shader->setMat4("model", panel.transform);
		panel.shader->setMat4("view", view);
		panel.shader->setMat4("projection", projection);
		panel.shadedDraw();
	}
}

void Box::transform(glm::mat4 &transformation)
{
	for (WoodenPanel &panel : panels)
	{
		panel.transform = transformation * panel.transform;
	}
}
