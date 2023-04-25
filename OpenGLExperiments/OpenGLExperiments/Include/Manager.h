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
	friend class BallPhysicsInput;
protected: 
	unsigned int VBO_pos{ 0 };
	unsigned int VBO_radius{ 0 };

	std::vector<glm::vec3> position;
	std::vector<float> mass;
	std::vector<float> restitution;
	std::vector<glm::vec3> velocity;
	std::vector<float> halfWidth;

public:
	float max_restitution = 0.9f;
	float min_restitution = 0.3f;
	int count = 0;
	float gravity = 9.8f;
	const float boundarySize = 100.0f;
	const float maxSpeed = 30.0f;
	const float maxWidth = 10.0f;
	std::unique_ptr<Model> object;
	float time = 0.0f;


	void generateBuffers();
	//coplanar objects make it easier to view bugs in collision code
	void spawnCoplanarObjects(int n);
	void spawnObjects(int n);
	void spawnObject(glm::vec3 new_position, glm::vec3 new_velocity, float new_radius);
	void updatePositions(float deltaTime);

	float randomVal(float magnitude, bool onlyPositive = false);
	glm::vec3 randomVec3(float magnitude);

	//pure virtual function for maintaining abstract class status, can iclude collsion detection in this loop
	virtual void update(float deltaTime) = 0;

	void drawObjects(Camera camera);
};

