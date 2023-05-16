// Shader.vert
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;
out vec2 texCoords;

out vec3 geometry_worldPos;
out vec4 geometry_gl_Position;
out vec3 geometry_normal;
out vec2 geometry_texCoords;


void main()
{
	normal = mat3(transpose(inverse(model))) * aNormal;
	//normal = aNormal;
	geometry_normal = normal;

	worldPos = (model * vec4(aPos, 1)).xyz;

	geometry_worldPos = worldPos;

	gl_Position = projection * view * vec4(worldPos, 1.0);
	geometry_gl_Position = gl_Position;

	texCoords = vec2(aTexCoords.x, aTexCoords.y);
	geometry_texCoords = texCoords;
}

// #geometry
// Shader.geom
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 geometry_worldPos[];
in vec2 geometry_texCoords[];
in vec4 geometry_gl_Position[];
in vec3 geometry_normal[];
out vec3 normal;
out vec3 worldPos;
out vec2 texCoords;

uniform float time;
uniform vec3 objectCenter;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// Input points
	vec3 p0 = geometry_worldPos[0];
	vec3 p1 = geometry_worldPos[1];
	vec3 p2 = geometry_worldPos[2];

	// Calculate triangle normal
	vec3 _normal = normalize(cross(p1 - p0, p2 - p0));

	// Check if the normal is facing away from the object center and flip if it does
	_normal = (dot(normal, objectCenter - p0) > 0.0) ? -_normal : _normal;
	//_normal = normalize(geometry_normal[0] + geometry_normal[1] + geometry_normal[2]);
	// Emit the triangle vertices

	texCoords = geometry_texCoords[0];
	normal = length(geometry_normal[0]) > 0 ? geometry_normal[0] : _normal;
	worldPos = p0 + _normal * time;
	gl_Position = projection * view * vec4(worldPos, 1.0);
	EmitVertex();


	texCoords = geometry_texCoords[1];
	normal = length(geometry_normal[1]) > 0 ? geometry_normal[1] : _normal;
	worldPos = p1 + _normal * time;
	gl_Position = projection * view * vec4(worldPos, 1.0);
	EmitVertex();

	texCoords = geometry_texCoords[2];
	normal = length(geometry_normal[2]) > 0 ? geometry_normal[2] : _normal;
	worldPos = p2 + _normal * time;
	gl_Position = projection * view * vec4(worldPos, 1.0);
	EmitVertex();

	EndPrimitive();
}

// Shader.frag

#version 330 core
out vec4 FragColor;

in vec3 worldPos;
in vec3 normal;
in vec2 texCoords;

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
uniform sampler2D diffuse_texture;

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
	vec3 color = texture(diffuse_texture, texCoords).rgb;
	color = length(color) == 0 ? vec3(1) : color;
	FragColor = vec4((ambientComponent + specularComponent + diffuseComponent) * color, 1);




}
