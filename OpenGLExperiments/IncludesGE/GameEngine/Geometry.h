#pragma once
#include "glm/vec3.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "GameEngine/PrimitiveRenderer.h"

#define DEBUG 0;

namespace Geometry
{
	//normalized axes
	constexpr glm::vec3 CubeAxes[7] = {
		//parallel to centre to centre of faces
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		//from centre to corners on one side
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f)
	};

	constexpr glm::vec3 CubeCorners[8] = {
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, 0.5f, 0.5f),
	glm::vec3(0.5f, 0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, 0.5f, -0.5f)
	};

	struct plane {
		glm::vec3 point;
		glm::vec3 normal;
	};

	bool test_behind_plane(const glm::vec3& point, const plane& p)
	{
		return glm::dot(point - p.point, p.normal) <= 0.0f;
	}

	struct axis_projection
	{
		float max_projection = -std::numeric_limits<float>::max();
		float min_projection = std::numeric_limits<float>::max();
		glm::vec3 minimum_point = glm::vec3(0);
		glm::vec3 maximum_point = glm::vec3(0);

	};

	axis_projection project_on_axis(const glm::vec3& axis, const std::vector<glm::vec3>& points)
	{
		//ensure axis is normalized
		auto axis_n = glm::normalize(axis);

		axis_projection limits;

		for (const auto& point : points)
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

	void generate_cube_faces(const glm::mat4& cubeTransform, std::vector<plane>& faces)
	{
		faces.clear();

		for (int i = 0; i < 3; i++)
		{
			Geometry::plane face_positive;
			face_positive.normal = normalize(glm::vec3(cubeTransform * glm::vec4(CubeAxes[i], 1) - cubeTransform * glm::vec4(0, 0, 0, 1)));
			face_positive.point = glm::vec3(cubeTransform * glm::vec4(0.5f * CubeAxes[i], 1));
			Geometry::plane face_negative;
			face_negative.normal = -face_positive.normal;
			face_negative.point = glm::vec3(cubeTransform * glm::vec4(-0.5f * CubeAxes[i], 1));
			faces.push_back(face_positive);
			faces.push_back(face_negative);
#if DEBUG == 1
			PrimitiveRenderer::DrawLines(std::vector<glm::vec3>({ face_positive.point, face_positive.point + face_positive.normal, }), i);
			PrimitiveRenderer::DrawLines(std::vector<glm::vec3>({ face_negative.point,face_negative.point + face_negative.normal }), i);
#endif
		}

	}

	void generate_face_points(glm::mat4 cubeTransform, std::vector<glm::vec3>& points)
	{
		for (int i = 0; i < 3; i++)
		{
			auto face_positive = glm::vec3(cubeTransform * glm::vec4(0.5f * CubeAxes[i], 1));
			auto face_negative = glm::vec3(cubeTransform * glm::vec4(-0.5f * CubeAxes[i], 1));
			points.push_back(face_positive);
			points.push_back(face_negative);
#if DEBUG == 2
			PrimitiveRenderer::DrawPoints(std::vector<glm::vec3>({ face_positive }), i);
			PrimitiveRenderer::DrawPoints(std::vector<glm::vec3>({ face_negative }), i);
#endif
		}
	}

	void generate_SAT_axes_for_cube(const glm::mat4& cubeTransform, std::vector<glm::vec3>& axes)
	{
		auto centre = glm::vec3(cubeTransform * glm::vec4(0, 0, 0, 1));
		for (auto axis : CubeAxes)
		{
			axes.push_back(glm::normalize(glm::vec3(cubeTransform * glm::vec4(axis, 1)) - centre));
#if DEBUG == 3
			PrimitiveRenderer::DrawLines(std::vector<glm::vec3>({ centre, centre + axes.back() }), 2);
#endif
		}
	}

	bool test_points_inside_cube(const glm::mat4& cubeTransform, const std::vector<glm::vec3>& points, glm::vec3& contact_point)
	{
		std::vector<plane> faces;

		generate_cube_faces(cubeTransform, faces);
		assert(faces.size() == 6);


		for (const auto& point : points)
		{
			bool inside_cube = true;

			for (const plane& face : faces)
			{
				if (!test_behind_plane(point, face))
				{
					inside_cube = false;
					break;
				}
			}
			if (inside_cube)
			{
				contact_point = point;
				return true;
			}
		}
		return false;
	}


	// returns overlap of points projected on axis, updates contact point
	float test_seperating_axis(const glm::vec3& axis, const std::vector<glm::vec3>& pointsA, const std::vector<glm::vec3>& pointsB, glm::vec3& contact_point, bool& isAlower)
	{

		Geometry::axis_projection limitsA = Geometry::project_on_axis(axis, pointsA);
		Geometry::axis_projection limitsB = Geometry::project_on_axis(axis, pointsB);

		// Check for overlap
		float overlap = std::min(limitsA.max_projection, limitsB.max_projection) - std::max(limitsA.min_projection, limitsB.min_projection);

		if (overlap < 0)
			return overlap;

		isAlower = limitsA.max_projection < limitsB.max_projection;

		// Update the contact point based on the corners contributing to the minimum and maximum projections, average them

		if (isAlower)
		{
			contact_point = 0.5f * (limitsA.maximum_point + limitsB.minimum_point);
		}
		else
		{
			contact_point = 0.5f * (limitsA.minimum_point + limitsB.maximum_point);
		}

		return overlap;
	}




}