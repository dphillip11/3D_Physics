#version 330
out vec4 FragColor;
in vec3 FragPos;
in vec3 colorGS;


uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform vec3 lightColor;
uniform vec3 materialColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;


//in vec4 color;
void main()
{
	// diffuse component
	vec3 norm = normalize(FragPos);
	vec3 lightDir = normalize(lightPosition - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseIntensity * diff * lightColor;

	//ambient component
	vec3 ambient = ambientIntensity * lightColor;

	//specular component
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 5);
	vec3 specular = specularIntensity * spec * lightColor;

	// FragColor = vec4((ambient + diffuse + specular) * materialColor,1);
	FragColor = vec4(1, 0, 0, 1);

}