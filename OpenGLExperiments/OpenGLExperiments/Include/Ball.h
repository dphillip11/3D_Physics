#pragma once
#include "Model.h"
#include <vector>
#include <glm/glm/vec3.hpp>
#include "Shader.h"
#include <memory>




class Ball : public Model
{	
	static const float X;
	static const float Z;
		
	//using subdivision improves memory usage, whereas not using it improves computational load on rendering
	static const int subdivided = false;
	static const int NUM_SEGMENTS = 40;
	
public:
	static const std::vector<glm::uvec3> _indices;
	static const std::vector<glm::vec3> _vertices;

	Ball();

	void CreateVertices();
	void useSimpleVertices();
	void shadedDraw(GLenum fillMode = GL_FILL, GLenum drawMode = GL_TRIANGLES);
};

	