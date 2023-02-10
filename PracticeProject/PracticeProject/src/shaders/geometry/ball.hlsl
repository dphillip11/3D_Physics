#version 330
in vec4 color[];
out vec4 colorGS;

layout(triangles) in;
layout(triangle_strip, max_vertices = 48) out;

uniform mat4 MVP;

vec4 colors[18];
vec3 positions[18];



//this script splits the edges of the triangle in half then do it agin, then fills the hole
void subdivideTriangle(int A, int B, int C, int index, bool emit)
{
    //mix positions
    positions[index]        = normalize(positions[A] + positions[B]);
    positions[index + 1]    = normalize(positions[A] + positions[C]);
    positions[index + 2]    = normalize(positions[B] + positions[C]);
    //mix colors
    colors[index]       = mix(colors[A], colors[B], 0.5);
    colors[index + 1]   = mix(colors[A], colors[C], 0.5);
    colors[index + 2]   = mix(colors[B], colors[C], 0.5);
    //mix textures

    //emit all vertice
    int indices[12] = int[12](A, index, index + 1, index, B, index + 2, index + 1, index + 2, C, index, index + 1, index + 2);
    //0,3,4, 3,1,5, 4,5,2

    int i;
    for (i = 0; i < 12; i++)
    {
        gl_Position = MVP * vec4(positions[indices[i]],1);
        colorGS = colors[indices[i]];

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
    positions[0] = normalize(gl_in[0].gl_Position.xyz);
    positions[1] = normalize(gl_in[1].gl_Position.xyz);
    positions[2] = normalize(gl_in[2].gl_Position.xyz);


    colors[0] = color[0];
    colors[1] = color[1];
    colors[2] = color[2];


    subdivideTriangle(0, 1, 2, 3, false);
    subdivideTriangle(0, 3, 4, 6, true);
    subdivideTriangle(3, 1, 5, 9, true);
    subdivideTriangle(4, 5, 2, 12, true);
    subdivideTriangle(3, 4, 5, 15, true);

    //emit final triangle
    gl_Position = MVP * vec4(positions[15],1) ;
    colorGS = colors[15];
    EmitVertex();

    gl_Position = MVP * vec4(positions[16],1) ;
    colorGS = colors[16];
    EmitVertex();

    gl_Position = MVP * vec4(positions[17],1) ;
    colorGS = colors[17];
    EmitVertex();

    EndPrimitive();


}
