#version 330
//geometry shader
layout(triangles) in;
layout(triangle_strip, max_vertices = 146) out;

in vec4 color[];
in vec4 position[];
in float height[];
in float width[];
out vec3 worldPos;
out vec4 gColor;
out vec3 normal;
uniform mat4 MVP;

void main()
{
	int indices[36] = {
			0,2,3,0,3,1, //bottom
			4,5,7,4,7,6, //top
			0,4,6,0,6,2,	
			1,7,5,3,7,1,
			1,5,4,1,4,0,
			2,6,3,3,6,7
	};

	for (int j = 0; j < 3; j++)
	{
	
		vec4 vertices[8] = {
			//left,0			top-left,1			right,2				top-right,3

			vec4(0,0,0,0),			vec4(0,0,width[j],0),			vec4(width[j],0,0,0),			vec4(width[j],0,width[j],0),			//bottom

			vec4(0,height[j],0,0),	vec4(0,height[j],width[j],0),	vec4(width[j],height[j],0,0),	vec4(width[j],height[j],width[j],0)		//top
			//4					5					6					7
		};


		

	
		for (int i = 0; i < 12; i++)
		{
			//get vertex coordinates
			vec3 pos[3] = vec3[3](vertices[indices[3 * i]].xyz + position[j].xyz,
								vertices[indices[3 * i + 1]].xyz + position[j].xyz,
								vertices[indices[3 * i + 2]].xyz + position[j].xyz);

			vec3 vertex_normal = normalize(cross((pos[2] - pos[1]), (pos[1] - pos[0])));

			for (int k = 0; k < 3; k++)
			{
				gl_Position = MVP * vec4(pos[k], 1);
				worldPos = pos[k];
				gColor = color[0];
				normal = vertex_normal;
				EmitVertex();
			}
			EndPrimitive();
		}
	}


}