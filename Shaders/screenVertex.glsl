#version 330 core

layout (location = 0) in vec2 vertexPos;

out vec2 fragmentTextureCoords;

void main()
{
    gl_Position = vec4(vertexPos, 0.0, 1.0);
    fragmentTextureCoords = (vertexPos + 1) / 2;
}