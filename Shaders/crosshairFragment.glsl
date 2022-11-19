#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 fragmentTextureColor = texture(screenTexture, fragmentTextureCoords);
    outputColor = vec4(vec3(1.0, 1.0, 1.0) - fragmentTextureColor.xyz, 1.0);
}