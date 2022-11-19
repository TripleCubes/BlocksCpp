#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform bool horizontal;
uniform sampler2D screenTexture;

float bell(float x)
{
    float a = x / 0.025;
    return exp(-0.5*a*a);
}

void main()
{
    vec3 result = vec3(0, 0, 0);
    vec2 step = 1.0 / textureSize(screenTexture, 0);
    float blurRange = 0.1;

    if (!horizontal)
    {
        float y = fragmentTextureCoords.y - blurRange;
        while (y < fragmentTextureCoords.y + blurRange)
        {
            result += texture(screenTexture, vec2(fragmentTextureCoords.x, y)).xyz * bell(y - fragmentTextureCoords.y);
            y += step.y;
        }
        result /= ((blurRange * 2) / step.y);
    }
    else
    {
        float x = fragmentTextureCoords.x - blurRange;
        while (x < fragmentTextureCoords.x + blurRange)
        {
            result += texture(screenTexture, vec2(x, fragmentTextureCoords.y)).xyz * bell(x - fragmentTextureCoords.x);
            x += step.x;
        }
        result /= ((blurRange * 2) / step.x);
    }

    outputColor = vec4(result * 2, 1.0);
}