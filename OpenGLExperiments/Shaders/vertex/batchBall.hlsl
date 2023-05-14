#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 ballPos;
layout(location = 2) in float ballHalfWidth;


out vec4 colorGS;
out vec3 worldPos;
out vec3 normal;

uniform mat4 VP;

mat4 translate(vec3 v) {
	mat4 result = mat4(1.0);
	result[3] = vec4(v, 1.0);
	return result;
}

mat4 scale(mat4 matrix, vec3 v) {
	mat4 result = matrix;
	result[0][0] *= v.x;
	result[1][1] *= v.y;
	result[2][2] *= v.z;
	return result;
}

void main()
{
	mat4 model = translate(ballPos);
	model = scale(model, vec3(ballHalfWidth, ballHalfWidth, ballHalfWidth));
	mat4 MVP = VP * model;
	//apply a color
	colorGS = vec4(30 * gl_InstanceID % 255, (30 * gl_InstanceID + 210) % 255, (30 * gl_InstanceID + 95) % 255, 255)/255.0f;
	//apply a transformation
	gl_Position = MVP * vec4(aPos, 1.0);
	worldPos = vec3(model * vec4(aPos, 1));
	normal = normalize(worldPos - ballPos);

}