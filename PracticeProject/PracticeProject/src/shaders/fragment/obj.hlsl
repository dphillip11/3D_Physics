//fragment shader
#version 330 core
out vec4 FragColor;

in vec3 worldPos;
in vec3 normal;
// in vec2 texCoord;

//uniform float time;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPosition;


void main()
{

	vec3 lightDir = normalize(worldPos - light.position);
	vec3 reflectDir = normalize(reflect(normal, -lightDir));
	vec3 viewDir = normalize(worldPos - viewPosition);

	//ambient
	vec3 ambientComponent = material.ambient * light.ambient;
		
	//diffuse
	float diffuseValue = max(dot(-lightDir, normal), 0);
	vec3 diffuseComponent = diffuseValue * material.diffuse * light.diffuse;
	
	//specular
	float specularValue = pow(max(dot(reflectDir, -viewDir), 0), material.shininess);
	vec3 specularComponent = material.specular * specularValue * light.specular;

	//result
	FragColor = vec4((ambientComponent + specularComponent + diffuseComponent), 1);

	


}