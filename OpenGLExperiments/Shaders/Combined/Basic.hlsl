// Shader.vert

#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 normal;
out vec3 worldPos;
out vec2 texCoords;

void main()
{
	normal = mat3(transpose(inverse(u_model))) * aNormal;

	worldPos = (u_model * vec4(aPos, 1)).xyz;

	texCoords = vec2(aTexCoords.x, aTexCoords.y);

	gl_Position = u_projection * u_view * vec4(worldPos, 1.0);

}

// Shader.frag

#version 330 core
out vec4 FragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoords;

uniform bool wireframe;

vec3 light_position = vec3(10, 10, 20);
vec3 viewPosition = vec3(0, 0, -2);
float cAmbient = 0.3f;
float cSpecular = 0.2f;
float cDiffuse = 0.4f;

int shininess = 50;

void main()
{
	if (!wireframe)
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
	else
	{
		FragColor = vec4(1, 0, 0, 1);
	}


}

