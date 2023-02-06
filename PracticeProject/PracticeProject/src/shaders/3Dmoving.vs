#version 330
layout(location = 0) in vec3 aPos;
out vec2 texCoord;
out vec4 color;
uniform vec3 offset;
void main()
{
gl_Position = vec4(aPos + offset,1.0f);
texCoord = vec2((aPos.x / abs(aPos.x)) * sqrt(aPos.x*aPos.z*aPos.x*aPos.z) * 4, (aPos.y/abs(aPos.y)) * sqrt(aPos.y*aPos.z * aPos.y*aPos.z) * 4 );
color = vec4(1.0f,1.0f,1.0f,1.0f);
}