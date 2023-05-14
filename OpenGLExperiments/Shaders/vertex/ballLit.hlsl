//#version 330
//layout(location = 0) in vec3 aPos;
//out vec4 colorGS;
//uniform mat4 MVP;
//uniform float ambientIntensity;
//uniform vec3 lightColor;
//uniform vec3 materialColor;
//uniform vec3 lightPosition;
//
//void main()
//{
//	//our sphere is centred at zero so the position is in the same direction as the normal
//	vec3 normal = normalize(aPos);
//	vec3 lightDirection = normalize(-aPos + lightPosition);
//	float diffuseIntensity = max(dot(normal, lightDirection),0);
//	vec3 diffuseLight = diffuseIntensity * lightColor;
//
//	vec3 ambientLight = ambientIntensity * lightColor;
//	//apply a color
//	colorGS = vec4(((ambientLight + diffuseLight) * materialColor),1);
//	//apply a transformation
//	gl_Position = MVP * vec4(aPos, 1.0);
//
//}

///perform in frag shader
#version 330
layout(location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 MVP;

void main()
{
	//our sphere is centred at zero so the position is in the same direction as the normal

	FragPos = aPos;
	gl_Position = MVP * vec4(aPos, 1.0);

}