#version 330
out vec4 FragColor;

int SCR_WIDTH = 1200;
int SCR_HEIGHT = 800;
int MAX_ITER = 100;


int calculateIter(vec2 c)
{
	vec2 z = c;
	int iter = 0;
	while (length(z) < 2. && iter < MAX_ITER)
	{
		float real = z.x * z.x + (-z.y * z.y) + c.x;
		float imaginary = (2. * z.x * z.y) + c.y;
		z = vec2(real, imaginary);
		iter++;
	}
	return iter;
}

void main()
{
	//normalize coordinates between -2 and 2 in both directions
	float real = (4 * (gl_FragCoord.x / SCR_WIDTH)) - 2;
	float imaginary = (4 * (gl_FragCoord.y / SCR_HEIGHT)) - 2;


	vec2 complex = vec2(real, imaginary);
	vec2 z = complex;
	int iterations = calculateIter(complex);

	FragColor = vec4((sin(iterations%10) + 1)/2, (sin(iterations + 1) + 1)/2, (sin(iterations + 2) + 1)/2, 1);
	
}
