#version 330 core
in float z;
out vec4 FragColor;
void main() 
{
    //float grenish = ;
    //float redish = ;
    FragColor = vec4(z, 1 - z, 0.0, 1.0);
}
