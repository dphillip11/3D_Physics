#version 330
layout(location = 0) in vec3 aPos;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
    //apply a transformation
    gl_Position = transform * vec4(aPos, 1.0f);
    //output texture coordinates
    texCoord = (aPos.xy + vec2(1, 1)) * 0.5;
}