#version 330
out vec4 FragColor;

int SCR_WIDTH = 1200;
int SCR_HEIGHT = 800;
int MAX_ITER = 100;

void main()
{
	//normalize coordinates between -2 and 2 in both directions
	float real = (4 * (gl_FragCoord.x / SCR_WIDTH)) - 2;
	float imaginary = (4 * (gl_FragCoord.y / SCR_HEIGHT)) - 2;


	vec2 complex = vec2(real, imaginary);
	vec2 z = complex;
	int iterations = 0;

	for (int i = 0; i < MAX_ITER; i++)
	{
		if (length(z) < 2)
			break;
		vec2 temp;
		temp = vec2( pow(z.x, 2) + complex.x, -pow(z.y, 2) + complex.y);
		z = temp;
		iterations++;
	}

	FragColor = vec4((sin(iterations) + 1)/2, (sin(iterations + 1) + 1)/2, (sin(iterations + 2) + 1)/2, 1);
	
}
