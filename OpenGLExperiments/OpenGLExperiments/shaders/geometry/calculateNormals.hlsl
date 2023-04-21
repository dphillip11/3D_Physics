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

uniform vec3 objectCenter;

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
    gl_Position = geometry_gl_Position[0];
    texCoords = geometry_texCoords[0];
    normal = _normal;
    worldPos = p0;
    EmitVertex();

    gl_Position = geometry_gl_Position[1];
    texCoords = geometry_texCoords[1];
    normal = _normal;
    worldPos = p1;
    EmitVertex();

    gl_Position = geometry_gl_Position[2];
    texCoords = geometry_texCoords[2];
    normal = _normal;
    worldPos = p2;
    EmitVertex();

    EndPrimitive();
}
