#pragma once
#include <vector>
#include <glm/glm/vec3.hpp>

const float X = 0.525731f;
const float Z = 0.850651f;

const std::vector<glm::vec3> positions =
{
glm::vec3(-X, 0.0f, Z), glm::vec3(X, 0.0f, Z), glm::vec3(-X, 0.0f, -Z), glm::vec3(X, 0.0f, -Z),
glm::vec3(0.0f, Z, X), glm::vec3(0.0f, Z, -X), glm::vec3(0.0f, -Z, X), glm::vec3(0.0f, -Z, -X),
glm::vec3(Z, X, 0.0f), glm::vec3(-Z, X, 0.0f), glm::vec3(Z, -X, 0.0f), glm::vec3(-Z, -X, 0.0f)
};

const std::vector<glm::uvec3> indices =
{
glm::uvec3(1, 4, 0),glm::uvec3(4, 9, 0),glm::uvec3(4, 5, 9),glm::uvec3(8, 5, 4),glm::uvec3(1, 8, 4),
glm::uvec3(1, 10, 8),glm::uvec3(10, 3, 8),glm::uvec3(8, 3, 5),glm::uvec3(3, 2, 5),glm::uvec3(3, 7, 2),
glm::uvec3(3, 10, 7),glm::uvec3(10, 6, 7),glm::uvec3(6, 11, 7),glm::uvec3(6, 0, 11),glm::uvec3(6, 1, 0),
glm::uvec3(10, 1, 6),glm::uvec3(11, 0, 9),glm::uvec3(2, 11, 9),glm::uvec3(5, 2, 9),glm::uvec3(11, 2, 7)
};



