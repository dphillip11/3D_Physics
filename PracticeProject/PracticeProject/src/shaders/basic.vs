#version 330
layout(location = 0) in vec3 aPos;
out vec4 color; uniform vec3 spherePos; uniform mat4 transform;
out vec2 texCoord;
void main()
{
    color = vec4(aPos.x + 0.5, aPos.y + 0.5, aPos.z + 0.5, 1.0f);
    gl_Position =  transform * vec4(aPos,1.0f);
    texCoord = (aPos.xy + vec2(1,1)) * 0.5;
}