#version 330
in vec4 color[];
out vec4 colorGS;
layout(triangles) in;
layout(triangle_strip, max_vertices = 84) out;

vec4 colors[27];
vec4 positions[27];
//this script splits the edges of the triangle in half then do it agin, then fills the hole
void subdivideTriangle(int A, int B, int C, int index)
{
    //mix positions
    positions[index] = mix(positions[A], positions[B], 0.5);
    positions[index + 1] = mix(positions[A], positions[C], 0.5);
    positions[index + 2] = mix(positions[B], positions[C], 0.5);
    //mix colors
    colors[index] = mix(colors[A], colors[B], 0.5);
    colors[index + 1] = mix(colors[A], colors[C], 0.5);
    colors[index + 2] = mix(colors[B], colors[C], 0.5);
    //emit all vertice
    int indices[9] = int[9](A, index, index+1, index, B, index+2, index+1, index+2, C);
    //0,3,4, 3,1,5, 4,5,2

    int i;
    for (i = 0; i < 9; i++)
    {
        gl_Position = positions[indices[i]];
        colorGS = colors[indices[i]];
        EmitVertex();
        if ((i + 1) % 3 == 0)
        {
            //emit triangle every 3 vertices
            EndPrimitive();
        }
    }
}

void main()
{
    positions[0] = gl_in[0].gl_Position;
    positions[1] = gl_in[1].gl_Position;
    positions[2] = gl_in[2].gl_Position;


    colors[0] = color[0];
    colors[1] = color[1];
    colors[2] = color[2];

    subdivideTriangle(0, 1, 2, 3);
    subdivideTriangle(0, 3, 4, 6);
    subdivideTriangle(3, 1, 5, 9);
    subdivideTriangle(4, 5, 2, 12);
    subdivideTriangle(3, 4, 5, 15);

    //emit final triangle
    gl_Position = positions[3];
    colorGS = colors[3];
    EmitVertex();
    gl_Position = positions[4];
    colorGS = colors[4];
    EmitVertex();
    gl_Position = positions[5];
    colorGS = colors[5];
    EmitVertex();
    EndPrimitive();


}
