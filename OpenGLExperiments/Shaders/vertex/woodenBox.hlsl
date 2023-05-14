#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view; 
uniform mat4 projection;

out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;


void main()
{
	texCoord = aTexCoords;
	normal = mat3(transpose(inverse(model))) * aNormal;
	worldPos = (model * vec4(aPos,1)).xyz;
	gl_Position = projection * view * vec4(worldPos, 1.0);

}