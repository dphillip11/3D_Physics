#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec3 offset;
uniform mat4 transform;

out vec4 color;
out vec2 texCoord;

void main()
{
	gl_Position = (transform * vec4(aPos ,1.0f)) + vec4(offset,1.0f);
	color = aColor;
	texCoord = aTexCoord;
}