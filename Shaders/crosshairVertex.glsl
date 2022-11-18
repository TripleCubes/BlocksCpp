#version 330 core

layout (location = 0) in vec2 vertexPos;
uniform vec2 windowSize;

void main()
{
    vec2 resultPos;
    resultPos.x = 2.0 / windowSize.x * vertexPos.x;
    resultPos.y = 2.0 / windowSize.y * vertexPos.y;
    gl_Position = vec4(resultPos, 0.0, 1.0);
}