#include "Camera.h"
#include <glm/glm/detail/func_trigonometric.inl>

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	_position = position;
	_target = target;
	updateValues();
}

glm::mat4 Camera::view()
{
	return lookAt();
}

void Camera::moveForward(float distance)
{
	_position = _position - (distance * glm::normalize(_direction));
}
void Camera::moveRight(float distance)
{
	_position = _position + (distance * glm::normalize(_right));
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
	updateValues();
}
void Camera::setTarget(glm::vec3 target) {
	_target = target;
	updateValues();
}

void Camera::rotate(float dx, float dy) 
{
	_yaw += dx;
	_pitch += dy;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_direction = glm::normalize(direction);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(up, _direction));
	_up = glm::cross(_direction, _right);
}

void Camera::updateValues()
{
	_direction = glm::normalize(_position - _target);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(up, _direction));
	_up = glm::cross(_direction, _right);
}

glm::mat4 Camera::lookAt()
{
	glm::mat4 lookat = glm::mat4(1);
	lookat[0] = glm::vec4(_right.x, _up.x, _direction.x, 0);
	lookat[1] = glm::vec4((float)_right.y, _up.y, _direction.y, 0);
	lookat[2] = glm::vec4(_right.z, _up.z, _direction.z, 0);
	glm::mat4 antiPos = glm::mat4(1);
	antiPos[3] = glm::vec4(-_position.x,-_position.y, -_position.z, 1);
	lookat = lookat * antiPos;
	return lookat;
}