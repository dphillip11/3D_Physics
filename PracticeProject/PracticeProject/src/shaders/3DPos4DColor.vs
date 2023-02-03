#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
uniform vec3 offset;
out vec4 vertexColor;
void main()
{
gl_Position = vec4(aPos + offset,1.0f);
vertexColor = aColor;
}