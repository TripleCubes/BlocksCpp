#version 330 core

out vec4 outputColor;
in vec2 fragmentTextureCoords;

uniform sampler2D positionTexture;
int numberOfRandomPoints = 10;
uniform vec3 randomPoints[10];
int numberOfRandomDirs = 16;
uniform vec3 randomDirs[16];

uniform mat4 projectionMat;
uniform mat4 viewMat;

vec2 rotate2D(float x, float y, float rotation)
{
    return vec2(x*cos(rotation) - y*sin(rotation), x*sin(rotation) + y*cos(rotation));
}

vec3 rotate3D(float x, float y, float z, float rotateX, float rotateY, float rotateZ)
{
    vec3 result = vec3(x, y, z);
    vec2 rotateResultX = rotate2D(result.y, result.z, rotateX);
    result.y = rotateResultX.x;
    result.z = rotateResultX.y;
    vec2 rotateResultY = rotate2D(result.x, result.z, rotateY);
    result.x = rotateResultY.x;
    result.z = rotateResultY.y;
    vec2 rotateResultZ = rotate2D(result.x, result.y, rotateZ);
    result.x = rotateResultZ.x;
    result.y = rotateResultZ.y;

    return result;
}

vec3 rotate3D(vec3 point, vec3 dir)
{
    return rotate3D(point.x, point.y, point.z, dir.x, dir.y, dir.z);
}

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec3 result = vec3(0, 0, 0);
    vec3 position = texture(positionTexture, fragmentTextureCoords).xyz;
    if (position == vec3(0.0, 0.0, 0.0))
    {
        result = vec3(1, 1, 1);
    } 
    else
    {
        for (int i = 0; i < numberOfRandomPoints; i++)
        {
            int randomDirIndex = abs(int(rand(fragmentTextureCoords * 100) * 100) % numberOfRandomDirs);
            vec3 checkPosition = position + rotate3D(randomPoints[i], randomDirs[randomDirIndex]) * 0.5;
            vec4 screenCheckPosition = projectionMat * viewMat * vec4(checkPosition, 1.0);
            screenCheckPosition.xyz /= screenCheckPosition.w;
            vec4 positionTextureCheck = vec4(texture(positionTexture, (screenCheckPosition.xy + vec2(1.0)) / 2).xyz, 1.0);
            positionTextureCheck = projectionMat * viewMat * positionTextureCheck;
            positionTextureCheck.xyz /= positionTextureCheck.w;
            if (positionTextureCheck.z > screenCheckPosition.z)
            {
                result += vec3(1.0 / numberOfRandomPoints);
            }
        }
    }

    // result += 0.2;
    // if (result.x > 1.0)
    // {
    //     result.x = 1.0;
    // }
    // if (result.y > 1.0)
    // {
    //     result.y = 1.0;
    // }
    // if (result.z > 1.0)
    // {
    //     result.z = 1.0;
    // }

    // vec4 screenCheckPosition = projectionMat * viewMat * vec4(position, 1.0);
    // screenCheckPosition.xyz /= screenCheckPosition.w;
    // result = vec3(screenCheckPosition.z);

    outputColor = vec4(result, 1.0);
}