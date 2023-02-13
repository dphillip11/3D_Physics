#pragma once
#include <glm/glm/matrix.hpp>
class Camera
{
private:
	glm::vec3 _target;
	glm::vec3 _up;
	glm::vec3 _right;
	float _FOV = 50;
	float _yaw = -90;
	float _pitch = 0;
	void updateValues();
public:
	glm::vec3 _direction;
	glm::vec3 _position;
	bool isLockedOn = false;
	glm::mat4 projection;
	Camera(glm::vec3 position, glm::vec3 target);
	void setPosition(glm::vec3);
	void setFOV(float fov);
	void zoom(float offset);
	void resetPitch();
	void setTarget(glm::vec3);
	void moveForward(float distance);
	void moveRight(float distance);
	void rotate(float dx, float dy);
	glm::mat4 lookAt();
	glm::mat4 view();
};

