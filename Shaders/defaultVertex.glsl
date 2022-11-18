#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureCoord;
out vec3 fragmentPos;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(vertexPos, 1.0);
    fragmentPos = (modelMat * vec4(vertexPos, 1.0)).xyz;
    fragmentNormal = vertexNormal;
    fragmentTextureCoord = vertexTextureCoord;
}