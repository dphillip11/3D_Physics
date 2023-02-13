#version 330
//vertex shader
layout(location = 0) in vec3 params;
//params.x = index, params.y = height, params.z = color
out vec4 color;
out vec4 position;
out float height;
out float width;
uniform int columns;
uniform float time;
int blockSpacing = 5;

void main()
{
	int index = int(params.x);
	int i = index % columns;
	int j = int(index - i)/columns ;
	height = params.y + 0.5f;
	width = 2.0f - (float(height) / 10);
	float heightF = (20 - height);
	float yPos = heightF * sin(i * 23 + j * 227 + time/4);
	position = vec4(blockSpacing * i, yPos, blockSpacing * j, 1);
	//color = vec4(sin(params.z), sin(1 + params.z), sin(2 + params.z), 1.0f);
	color = vec4(1);
}