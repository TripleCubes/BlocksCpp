#version 330 core

in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;
out vec4 outputColor;

uniform vec3 skyLightDir;
uniform vec3 fragmentColor;
uniform int numberOfLights;

struct Light
{
    vec3 pos;
    vec3 color;
};
uniform Light pointLights[20];

uniform sampler2D blockTextures;
uniform sampler2D blockLightTextures;

vec4 blockTextureFragmentColor;
vec4 blockLightTextureFragmentColor;
vec3 normal;

vec3 calcPointLights()
{
    vec3 result = vec3(0, 0, 0);
    for (int i = 0; i < numberOfLights; i++)
    {
        vec3 lightDir = normalize(pointLights[i].pos - fragmentPos);
        float diff = max(dot(normal, lightDir), 0);
        float distance = length(pointLights[i].pos - fragmentPos);
        float attenuation = 1.0 / (1 + 0.09 * distance + 0.032 * (distance * distance));  
        result += (blockTextureFragmentColor.xyz*0.5 + blockTextureFragmentColor.xyz*diff*0.5) * (attenuation * pointLights[i].color);
    }
    return result;
}

void main()
{
    normal = normalize(fragmentNormal);
    blockTextureFragmentColor = texture(blockTextures, fragmentTextureCoord);
    blockLightTextureFragmentColor = texture(blockLightTextures, fragmentTextureCoord);

    vec3 lightDir = normalize(-skyLightDir);
    float diff = max(dot(normal, lightDir), 0);
    
    vec3 result = blockTextureFragmentColor.xyz*0.1 + blockTextureFragmentColor.xyz*diff*0.1 + calcPointLights();
    result += vec3(blockTextureFragmentColor * blockLightTextureFragmentColor)*0.5;
    
    outputColor = vec4(result, 1.0);
}