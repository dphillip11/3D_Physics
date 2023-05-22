#include "PCH/pch.h"
#include "GameEngine/Quaternion.h"

glm::quat Quaternion::AxisAngleRadiansToQuaternion(const glm::vec3& axis, float angle)
{
	auto axis_normalized = glm::normalize(axis);
	// Here we calculate the sin( theta / 2) once for optimization
	double factor = sin(angle / 2.0);

	// Calculate the x, y and z of the quaternion
	float x = axis_normalized.x * factor;
	float y = axis_normalized.y * factor;
	float z = axis_normalized.z * factor;

	// Calcualte the w value by cos( theta / 2 )
	float w = cos(angle / 2.0);

	return glm::quat(x, y, z, w);
}

glm::quat Quaternion::AxisAngleDegreesToQuaternion(const glm::vec3& axis, float angleDegrees) {
	// Convert the angle from degrees to radians
	float angleRadians = glm::radians(angleDegrees);

	return AxisAngleRadiansToQuaternion(axis, angleRadians);
}

glm::quat Quaternion::EulerAnglesDegreesToQuat(const glm::vec3& angle)
{
	return glm::quat(glm::radians(angle));
}

glm::quat Quaternion::EulerAnglesRadiansToQuat(const glm::vec3& angle)
{
	return glm::quat(angle);
}

glm::quat Quaternion::ScaleQuaternion(const glm::quat& quaternion, float scale) {
	glm::vec3 axis = glm::axis(quaternion);
	float angle = glm::angle(quaternion);

	glm::vec3 scaledAxis = axis * scale;
	glm::quat scaledQuaternion = glm::angleAxis(angle, scaledAxis);

	return scaledQuaternion;
}


