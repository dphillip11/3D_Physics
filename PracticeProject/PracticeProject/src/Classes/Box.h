#pragma once
#include <vector>
#include "WoodenPanel.h"

class Box
{
	WoodenPanel panel;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> rotations;
	glm::mat4 _transform = glm::mat4(1);
	
public:
	std::vector<glm::mat4> boxTransforms;
	std::vector<glm::mat4> boxTransformations;
	Box();
	void draw(glm::mat4& view, glm::mat4& projection);
	void createBoxTransforms(int n);
	void drawBoxes(glm::mat4& view, glm::mat4& projection);
	void transform(glm::mat4 &transformation);
};

