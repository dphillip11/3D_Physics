#version 330
in vec4 color[];
out vec4 colorGS;
in vec2 texCoord[];
out vec2 TexCoordGS;
layout(triangles) in;
layout(triangle_strip, max_vertices = 48) out;


vec4 colors[18];
vec4 positions[18];
vec2 texCoords[18];
uniform vec3 spherePos;
uniform float radius;

//this script splits the edges of the triangle in half then do it agin, then fills the hole
void subdivideTriangle(int A, int B, int C, int index, bool emit)
{
    //mix positions
    positions[index] = vec4(radius * normalize(positions[A].xyz + positions[B].xyz), 1);
    positions[index + 1] = vec4(radius * normalize(positions[A].xyz + positions[C].xyz), 1);
    positions[index + 2] = vec4(radius * normalize(positions[B].xyz + positions[C].xyz), 1);
    //mix colors
    colors[index] = mix(colors[A], colors[B], 0.5);
    colors[index + 1] = mix(colors[A], colors[C], 0.5);
    colors[index + 2] = mix(colors[B], colors[C], 0.5);
    //mix textures
    texCoords[index] = mix(texCoords[A], texCoords[B], 0.5);
    texCoords[index + 1] = mix(texCoords[A], texCoords[C], 0.5);
    texCoords[index + 2] = mix(texCoords[B], texCoords[C], 0.5);
    //emit all vertice
    int indices[12] = int[12](A, index, index + 1, index, B, index + 2, index + 1, index + 2, C, index, index+1, index+ 2);
    //0,3,4, 3,1,5, 4,5,2

    int i;
    for (i = 0; i < 12; i++)
    {
        gl_Position = positions[indices[i]] + vec4(spherePos,0);
        colorGS = colors[indices[i]];
        TexCoordGS = texCoords[indices[i]];
        if (emit)
        {
            EmitVertex();
            if ((i + 1) % 3 == 0)
            {
                //emit triangle every 3 vertices
                EndPrimitive();
            }
        }
    }
}

void main()
{
    positions[0] = vec4(radius * normalize(gl_in[0].gl_Position.xyz - spherePos), 1);
    positions[1] = vec4(radius * normalize(gl_in[1].gl_Position.xyz - spherePos), 1);
    positions[2] = vec4(radius * normalize(gl_in[2].gl_Position.xyz - spherePos), 1);


    colors[0] = color[0];
    colors[1] = color[1];
    colors[2] = color[2];

    texCoords[0] = texCoord[0];
    texCoords[1] = texCoord[1];
    texCoords[2] = texCoord[2];

    subdivideTriangle(0, 1, 2, 3, false);
    subdivideTriangle(0, 3, 4, 6, true);
    subdivideTriangle(3, 1, 5, 9, true);
    subdivideTriangle(4, 5, 2, 12, true);
    subdivideTriangle(3, 4, 5, 15, true);

    //emit final triangle
    gl_Position = positions[15] + vec4(spherePos, 0);
    colorGS = colors[15];
    TexCoordGS = texCoords[15];
    EmitVertex();
    gl_Position = positions[16] + vec4(spherePos, 0);
    colorGS = colors[16];
    TexCoordGS = texCoords[16];
    EmitVertex();
    gl_Position = positions[17] + vec4(spherePos, 0);
    colorGS = colors[17];
    TexCoordGS = texCoords[17];
    EmitVertex();
    EndPrimitive();


}
