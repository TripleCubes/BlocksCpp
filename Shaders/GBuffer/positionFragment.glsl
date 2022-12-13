#version 330 core

in vec3 fragmentPos;
out vec4 outputColor;

void main()
{ 
    outputColor = vec4(fragmentPos, 1.0);
}