#version 330
layout(location = 0) in vec3 aPos;
out vec4 color;

uniform mat4 transform;
void main()
{
gl_Position =  transform * vec4(aPos,1.0f);
color = vec4(abs(gl_Position.x), abs(gl_Position.y), abs(gl_Position.z),1.0f);
}