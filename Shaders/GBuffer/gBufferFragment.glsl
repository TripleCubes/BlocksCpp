#version 330 core

layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;

in vec3 fragmentPos;
in vec3 fragmentNormal;

void main()
{ 
    position = fragmentPos;
    normal = fragmentNormal;
}