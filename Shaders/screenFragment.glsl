#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D screenTexture;
uniform sampler2D blurTexture;
uniform sampler2D ssaoTexture;

vec3 reinhard_extended(vec3 v, float max_white)
{
    vec3 numerator = v * (1.0f + (v / vec3(max_white * max_white)));
    return numerator / (1.0f + v);
}

void main()
{
    vec3 result;
    result = texture(screenTexture, fragmentTextureCoords).xyz * texture(ssaoTexture, fragmentTextureCoords).x + texture(blurTexture, fragmentTextureCoords).xyz;
    result = reinhard_extended(result, 2);

    // result = texture(ssaoTexture, fragmentTextureCoords).xyz;

    outputColor = vec4(result, 1.0);
}