#version 330
layout(location = 0) in vec3 aPos;
uniform float x;
uniform float y;
uniform float z;
void main()
{
gl_Position = vec4((aPos.x + x), (aPos.y + y), (aPos.z + z),1.0f);
}