
#version 330
out vec4 FragColor;

in vec4 colorGS;
in vec2 TexCoordGS;

uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoordGS);
}