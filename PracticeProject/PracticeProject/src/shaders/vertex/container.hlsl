#version 330
layout(location = 0) in vec3 aPos;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //apply a transformation
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //output texture coordinates
    texCoord = (aPos.xy + vec2(1, 1)) * 0.5;
}