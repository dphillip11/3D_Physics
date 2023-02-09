#pragma once
#include <glm/glm/matrix.hpp>
class Camera
{
private:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _direction;
	glm::vec3 _up;
	glm::vec3 _right;
	float _yaw = -90;
	float _pitch = 0;
	void updateValues();
public:
	Camera(glm::vec3 position, glm::vec3 target);
	void setPosition(glm::vec3);
	void setTarget(glm::vec3);
	void moveForward(float distance);
	void moveRight(float distance);
	void rotate(float dx, float dy);
	glm::mat4 lookAt();
	glm::mat4 view();
};

