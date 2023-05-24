#pragma once
#include "glm/vec3.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Geometry
{
	struct plane {
		glm::vec3 point;
		glm::vec3 normal;
	};

	bool test_behind_plane(glm::vec3 point, plane p)
	{
		return glm::dot(point - p.point, p.normal) < 0.0f;
	}

	struct axis_projection
	{
		float max_projection = -std::numeric_limits<float>::max();
		float min_projection = std::numeric_limits<float>::max();
		glm::vec3 minimum_point;
		glm::vec3 maximum_point;

	};

	axis_projection project_on_axis(glm::vec3 axis, std::vector<glm::vec3> points)
	{
		//ensure axis is normalized
		auto axis_n = glm::normalize(axis);

		axis_projection limits;

		for (auto point : points)
		{
			float projection = glm::dot(point, axis_n);
			if (projection < limits.min_projection)
			{
				limits.min_projection = projection;
				limits.minimum_point = point;
			}
			if (projection > limits.max_projection)
			{
				limits.max_projection = projection;
				limits.maximum_point = point;
			}
		}
		return limits;
	}

}