#version 330
//fragment shader
out vec4 FragColor;
in vec4 gColor;
//in vec4 color;
void main()
{
    FragColor = gColor;
}