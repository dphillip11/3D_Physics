#version 330
//geometry shader
layout(triangles) in;
layout(triangle_strip, max_vertices = 146) out;

in vec4 color[];
in vec4 position[];
in float height[];
in float width[];
out vec4 gColor;

uniform mat4 MVP;
uniform vec3 lightDirection;
uniform vec3 viewDirection;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;

void main()
{
	int indices[36] = {
			0,2,3,0,3,1,
			4,5,7,4,7,6,
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
			vec3 pos[3] = vec3[3](vertices[indices[3 * i]].xyz + position[j].xyz,
				vertices[indices[3 * i + 1]].xyz + position[j].xyz,
				vertices[indices[3 * i + 2]].xyz + position[j].xyz);
			vec3 normal = normalize(cross((pos[1] - pos[2]), (pos[1] - pos[0])));
			float diffuse = max(dot(normal, lightDirection), 0.0);
			vec3 reflect = reflect(-lightDirection, normal);
			float specular = pow(max(dot(reflect, viewDirection), 0.0), shininess);
			vec3 diffuseContrib = diffuse * diffuseColor;
			vec3 specularContrib = specular * specularColor;
			vec4 colorOut = vec4(ambientColor + diffuseContrib + specularContrib, 1.0) * color[j];
			for (int k = 0; k < 3; k++)
			{
				gl_Position = MVP * vec4(pos[k], 1);
				gColor = colorOut;
				EmitVertex();
			}
			EndPrimitive();
		}
	}


}