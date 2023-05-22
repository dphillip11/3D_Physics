#pragma once
class Quaternion {
public:
	static glm::quat AxisAngleRadiansToQuaternion(const glm::vec3& axis, float angle);
	static glm::quat AxisAngleDegreesToQuaternion(const glm::vec3& axis, float angleDegrees);
	static glm::quat EulerAnglesDegreesToQuat(const glm::vec3& angle);
	static glm::quat EulerAnglesRadiansToQuat(const glm::vec3& angle);
	static glm::quat ScaleQuaternion(const glm::quat& quaternion, float scale);
};