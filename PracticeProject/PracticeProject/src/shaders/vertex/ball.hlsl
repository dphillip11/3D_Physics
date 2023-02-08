#version 330
layout(location = 0) in vec3 aPos;
out vec4 color;
uniform mat4 transform;
void main()
{
	//apply a color
	color = vec4(aPos.x + 0.5, aPos.y + 0.5, aPos.z + 0.5, 1.0f);
	//apply a transformation
	gl_Position = transform * vec4(aPos, 1.0f);

}