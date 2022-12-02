#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 result = texture(screenTexture, fragmentTextureCoords).xyz;
    if (result.x < 1.5 && result.y < 1.5 && result.z < 1.5)
    {
        result = vec3(0, 0, 0);
    }

    outputColor = vec4(result, 1.0);
}