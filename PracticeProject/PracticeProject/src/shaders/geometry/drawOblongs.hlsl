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
uniform vec3 lightPosition;
uniform vec3 camPosition;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float shininess;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;

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
			//calculate normal to those coordinates
			vec3 normal = normalize(cross((pos[2] - pos[1]), (pos[1] - pos[0])));
			//ambient component
			vec3 ambient = ambientIntensity * ambientColor;
			//diffuse component
			//average light direction
			vec3 lightDirection = normalize(lightPosition - ((pos[0] + pos[1] + pos[2]) / 3));
			float diffuseStrength = max(dot(normal, lightDirection), 0.0);
			vec3 diffuse = diffuseIntensity * diffuseStrength * diffuseColor;
			//specular component
			vec3 reflectDir = normalize(reflect(-lightDirection, normal));
			vec3 viewDirection = normalize(camPosition - ((pos[0] + pos[1] + pos[2]) / 3));

			float specularStrength = pow(max(dot(viewDirection, reflectDir), 0.0), shininess);
			vec3 specular = specularStrength * specularIntensity * specularColor;
			
			vec4 colorOut = vec4(ambient + diffuse + specular, 1.0) * color[j];

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