#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 normal;
out vec3 worldPos;
out vec2 texCoords;

void main()
{
	normal = mat3(transpose(inverse(u_model))) * aNormal;
	
	worldPos = (u_model * vec4(aPos, 1)).xyz;

	texCoords = vec2(aTexCoords.x, aTexCoords.y);

	gl_Position = u_projection * u_view * vec4(worldPos, 1.0);

}