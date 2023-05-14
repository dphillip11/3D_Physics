#version 330
layout(location = 0) in vec3 aPos;
out vec4 colorGS;
out vec3 worldPos;
out vec3 normal;

uniform mat4 MVP;
uniform mat4 model;
uniform vec3 color;
uniform vec3 objectPos;

void main()
{
	//apply a color

	colorGS = vec4(color,1);
	//apply a transformation
	gl_Position = MVP * vec4(aPos, 1.0);
	worldPos = vec3(model * vec4(aPos, 1));
	normal = normalize(worldPos - objectPos);

}