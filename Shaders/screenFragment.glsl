#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D screenTexture;
uniform sampler2D blurTexture;

uniform int bloomMode;

void main()
{
    vec3 result;
    if (bloomMode == 0)
    {
        result = texture(screenTexture, fragmentTextureCoords).xyz + texture(blurTexture, fragmentTextureCoords).xyz;
    }
    else if (bloomMode == 1)
    {
        result = texture(screenTexture, fragmentTextureCoords).xyz;
    }
    else
    {
        result = texture(blurTexture, fragmentTextureCoords).xyz;
    }
    outputColor = vec4(result, 1.0);
}