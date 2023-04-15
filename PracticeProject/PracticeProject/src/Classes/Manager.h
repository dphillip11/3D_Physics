#pragma once
#include <vector>
#include <memory>
#include <glm/glm/vec3.hpp>
#include "Model.h"
#include "Camera.h"


struct pair {
	int a;
	int b;
};

//abstract base class for shape managers
class Manager
{
protected: 
	
	std::vector<glm::vec3> position;
	std::vector<glm::vec3> velocity;
	std::vector<float> halfWidth;

public:
	int count = 0;
	const float boundarySize = 75;
	const float maxSpeed = 50;
	const float maxWidth = 2;

	std::unique_ptr<Model> object;

	//coplanar objects make it easier to view bugs in collision code
	void spawnCoplanarObjects(int n);
	void spawnObjects(int n);
		
	void updatePositions(float deltaTime);

	float randomVal(float magnitude, bool onlyPositive = false);
	glm::vec3 randomVec3(float magnitude);

	//pure virtual function for maintaining abstract class status, can iclude collsion detection in this loop
	virtual void update(float delataTime) = 0;

	void drawObjects(Camera camera);
};

