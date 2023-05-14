#version 330
//fragment shader
out vec4 FragColor;
in vec4 gColor;
in vec3 worldPos;
in vec3 normal;

uniform vec3 lightPosition;
uniform vec3 camPosition;

vec3 ambientColor = vec3(1);
vec3 diffuseColor = vec3(1);
vec3 specularColor = vec3(1);

float shininess = 20;
float ambientIntensity = 0.1f;
float diffuseIntensity = 0.3f;
float specularIntensity = 0.3f;

void main()
{
	//ambient component
	vec3 ambient = ambientIntensity * ambientColor;
	//diffuse component
	vec3 lightDirection = normalize(lightPosition - worldPos);
	float diffuseStrength = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = diffuseIntensity * diffuseStrength * diffuseColor;
	//specular component
	vec3 reflectDir = normalize(reflect(-lightDirection, normal));
	vec3 viewDirection = normalize(camPosition - worldPos);

	float specularStrength = pow(max(dot(viewDirection, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * specularIntensity * specularColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0) * gColor;

}