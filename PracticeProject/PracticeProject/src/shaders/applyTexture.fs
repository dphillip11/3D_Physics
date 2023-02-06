
#version 330
out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;

uniform float t;
void main()
{
	FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1-texCoord.x,texCoord.y)), blend);
}