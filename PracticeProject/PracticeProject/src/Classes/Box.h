#pragma once
#include <vector>
#include "WoodenPanel.h"

class Box
{
	std::vector<WoodenPanel> panels;

public:
	Box();
	void draw(glm::mat4& view, glm::mat4& projection);
	void transform(glm::mat4 &transformation);
};

