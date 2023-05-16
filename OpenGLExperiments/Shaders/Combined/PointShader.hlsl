// Shader.vert
#version 330
layout(location = 0) in vec3 aPos;

uniform mat4 u_view;
uniform mat4 u_projection;


void main()
{

	gl_Position = u_projection * u_view * vec4(aPos, 1.0);

}


// Shader.frag
#version 330
out vec4 FragColor;

void main()
{

	FragColor = vec4(1, 0, 0, 1);

}
