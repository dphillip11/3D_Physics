
#version 330
out vec4 FragColor;
uniform float t;
void main()
{
	FragColor = vec4(0.5*(sin(t) + 1),0.5*(sin(t + 2) + 1),0.5*(sin(t + 4) + 1),1.0f);
}