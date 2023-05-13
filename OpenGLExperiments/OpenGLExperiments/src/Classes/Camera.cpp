#include "Camera.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>


Camera* Camera::currentCamera = nullptr;

Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	currentCamera = this;
	setFOV(_FOV);
	_position = position;
	_target = target;
	updateValues();
}

glm::mat4 Camera::view()
{
	return lookAt();
}

void Camera::zoom(float offset)
{
	_FOV += offset * zoomSpeed;
	if (_FOV < 1.0f)
		_FOV = 1.0f;
	if (_FOV > 110.0f)
		_FOV = 110.0f;
	setFOV(_FOV);
}

void Camera::setFOV(float fov)
{
	projection = glm::perspective(glm::radians(fov), (float)(1280 / 720), 0.1f, 1000.0f);
}

void Camera::moveForward(float distance)
{
	_position = _position - (moveSpeed * distance * glm::normalize(_direction));
}
void Camera::moveRight(float distance)
{
	_position = _position + (moveSpeed * distance * glm::normalize(_right));
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
	_direction = glm::normalize(_position - _target);
	updateValues();
}
void Camera::setTarget(glm::vec3 target) {
	_target = target;
	_direction = glm::normalize(_position - _target);
	updateValues();
}

void Camera::rotate(float dx, float dy)
{
	_yaw += dx * panSpeed;
	_pitch += dy * panSpeed;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	glm::vec3 direction;

	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_direction = glm::normalize(direction);

	updateValues();
}


void Camera::updateValues()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(up, _direction));
	_up = glm::cross(_direction, _right);
}

void Camera::resetPitch()
{
	_pitch = glm::degrees(asin(_direction.y));
	_yaw = glm::degrees(atan2(_direction.z, _direction.x));
}

glm::mat4 Camera::lookAt()
{
	if (isLockedOn)
	{
		setTarget(_target);
		resetPitch();
	}
	glm::mat4 lookat = glm::mat4(1);
	lookat[0] = glm::vec4(_right.x, _up.x, _direction.x, 0);
	lookat[1] = glm::vec4((float)_right.y, _up.y, _direction.y, 0);
	lookat[2] = glm::vec4(_right.z, _up.z, _direction.z, 0);
	glm::mat4 antiPos = glm::mat4(1);
	antiPos[3] = glm::vec4(-_position.x, -_position.y, -_position.z, 1);
	lookat = lookat * antiPos;
	return lookat;
}