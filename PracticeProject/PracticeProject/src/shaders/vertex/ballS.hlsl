#version 330
layout(location = 0) in vec3 aPos;
out vec4 colorGS;
uniform mat4 MVP;

void main()
{
	//apply a color
	colorGS = vec4(aPos.x + 0.5, aPos.y + 0.5, aPos.z + 0.5, 1.0f);
	//apply a transformation
	gl_Position = MVP * vec4(aPos, 1.0);

}