//fragment shader
#version 330 core
out vec4 FragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoords;


vec3 light_position = vec3(10,10,20);
vec3 viewPosition = vec3(0,0,-2);
float cAmbient = 0.3f;
float cSpecular = 0.2f;
float cDiffuse = 0.4f;

int shininess = 50;

void main()
{

	{
		vec3 lightDir = normalize(worldPos - light_position);
		vec3 reflectDir = normalize(reflect(normal, -lightDir));
		vec3 viewDir = normalize(worldPos - viewPosition);
		
		//diffuse
		float diffuseValue = max(dot(-lightDir, normal), 0);
	
		//specular
		float specularValue = pow(max(dot(reflectDir, -viewDir), 0), shininess);

		//result
		FragColor = vec4((diffuseValue * cDiffuse + cSpecular * specularValue + cAmbient) * vec3(1), 1);
	}


}