#version 330
layout(location = 0) in vec3 aPos;
out vec4 colorGS;
void main()
{
colorGS = vec4(aPos.x + 0.5, aPos.y + 0.5, aPos.z + 0.5, 1.0f);
gl_Position =  vec4(aPos,1.0f);

}