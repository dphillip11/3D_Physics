#version 330
in vec4 color[];
out vec4 colorGS;
layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

void main()
{
    vec4 A = gl_in[0].gl_Position;
    vec4 B = gl_in[1].gl_Position;
    vec4 C = gl_in[2].gl_Position;

    vec4 AB = mix(A, B, 0.5);
    vec4 AC = mix(A, C, 0.5);
    vec4 BC = mix(B, C, 0.5);

    vec4 colorA = color[0];
    vec4 colorB = color[1];
    vec4 colorC = color[2];

    vec4 colorAB = mix(colorA, colorB, 0.5);
    vec4 colorAC = mix(colorA, colorC, 0.5);
    vec4 colorBC = mix(colorB, colorC, 0.5);

    gl_Position = A;
    colorGS = colorA;
    EmitVertex();

    gl_Position = AB;
    colorGS = colorAB;
    EmitVertex();

    gl_Position = AC;
    colorGS = colorAC;
    EmitVertex();

    EndPrimitive();

    gl_Position = AB;
    colorGS = colorAB;
    EmitVertex();

    gl_Position = B;
    colorGS = colorB;
    EmitVertex();

    gl_Position = BC;
    colorGS = colorBC;
    EmitVertex();

    EndPrimitive();

    gl_Position = AC;
    colorGS = colorAC;
    EmitVertex();

    gl_Position = BC;
    colorGS = colorBC;
    EmitVertex();

    gl_Position = C;
    colorGS = colorC;
    EmitVertex();

    EndPrimitive();
}
