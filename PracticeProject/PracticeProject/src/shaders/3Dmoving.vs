#version 330
layout(location = 0) in vec3 aPos;
uniform vec3 offset;
void main()
{
gl_Position = vec4(aPos + offset,1.0f);
}