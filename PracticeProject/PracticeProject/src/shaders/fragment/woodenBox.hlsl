//fragment shader
#version 330 core
out vec4 FragColor;


in vec3 worldPos;
in vec3 normal;
in vec2 texCoord;

uniform float time;

struct Material 
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
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
	//ambient
	vec3 ambientComponent = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	vec3 lightDir = normalize(worldPos - light.position);
	float diffuseValue = max(dot(-lightDir, normal),0);
	//diffuse
	vec3 diffuseComponent = light.diffuse * diffuseValue * vec3(texture(material.diffuse, texCoord));
	//specular
	vec3 reflectDir = normalize(reflect(normal,-lightDir));
	vec3 viewDir = normalize(worldPos - viewPosition);
	float specularValue = pow(max(dot(reflectDir, -viewDir), 0), material.shininess);
	vec3 specularComponent = vec3(texture(material.specular, texCoord)) * specularValue * light.specular;

	vec3 emission = texture(material.emission, texCoord).rgb * floor(vec3(1.f) - texture(material.specular, texCoord).rgb);
	//result
	FragColor = vec4((ambientComponent + specularComponent + diffuseComponent + emission),1);


}