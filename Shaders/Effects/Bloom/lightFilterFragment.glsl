#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 result = texture(screenTexture, fragmentTextureCoords).xyz;
    if (result.x < 0.95 && result.y < 0.95 && result.z < 0.95)
    {
        result = vec3(0, 0, 0);
    }

    outputColor = vec4(result, 1.0);
}