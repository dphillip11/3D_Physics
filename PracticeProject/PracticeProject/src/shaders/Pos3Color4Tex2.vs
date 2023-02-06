#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec3 offset;

out vec4 color;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(aPos + offset,1.0f);
	color = aColor;
	texCoord = aTexCoord;
}