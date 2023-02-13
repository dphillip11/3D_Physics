#pragma once
#include <vector>
#include <memory>
#include <glm/glm/vec3.hpp>

struct pair {
	int a;
	int b;
};

class Manager
{
protected: 
	std::vector<glm::vec3> position;
	std::vector<glm::vec3> velocity;
	std::vector<float> halfWidth;

public:
	int count = 0;
	const float boundarySize = 200;
	const float maxSpeed = 20;
	const float maxWidth = 10;
	void updatePositions(float deltaTime);
	float randomVal(float magnitude, bool onlyPositive = false);
	glm::vec3 randomVec3(float magnitude);
};

