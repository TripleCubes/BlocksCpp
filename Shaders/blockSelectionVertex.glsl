#version 330 core

layout (location = 0) in vec3 vertexPos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertexPos, 1.0);
}