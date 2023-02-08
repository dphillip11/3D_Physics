#version 330
out vec4 FragColor;
in vec4 colorGS;
//in vec4 color;
void main()
{
    FragColor = colorGS;
}