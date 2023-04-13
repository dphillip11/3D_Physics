#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
// layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;
out vec3 geometry_worldPos;
out vec4 geometry_gl_Position;


void main()
{
	// texCoord = aTexCoords;
	//normal = mat3(transpose(inverse(model))) * aNormal;
	normal = normalize(vec3(sin(aPos.x),sin(aPos.y), sin(aPos.z)));
	worldPos = (model * vec4(aPos, 1)).xyz;
	geometry_worldPos = worldPos;
	gl_Position = projection * view * vec4(worldPos, 1.0);
	geometry_gl_Position = gl_Position;
}