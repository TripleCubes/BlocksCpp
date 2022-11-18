#include <iostream>
#include "shaders.h"

unsigned int compileShader(std::string path, ShaderType shaderType)
{
    std::ifstream file(path);
    if (file.fail())
    {
        std::cout << path << " not found" << std::endl;
        return -1;
    }
    std::string shaderCodeString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const char* shaderCode = shaderCodeString.c_str();
    unsigned int shader;

    if (shaderType == VERTEX)
    {
        shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "vertex shader compile error\n" << path << std::endl << infoLog << std::endl;
        }
    }
    else if (shaderType == FRAGMENT)
    {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "fragment shader compile error\n" << path << std::endl << infoLog << std::endl;
        }
    }

    return shader;
}

void linkShaderProgram(unsigned int shaderProgram, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    unsigned int vertexShader = compileShader(vertexShaderPath, VERTEX);
    unsigned int fragmentShader = compileShader(fragmentShaderPath, FRAGMENT);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "shader linking error\n" <<  infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader defaultShader;

void Shader::init(std::string vertexShaderPath, std::string fragmentShaderPath, bool hasMvpUniforms)
{
    shaderProgram = glCreateProgram();
    linkShaderProgram(shaderProgram, vertexShaderPath, fragmentShaderPath);
    if (hasMvpUniforms)
    {
        modelMatUniformLocation = glGetUniformLocation(shaderProgram, "modelMat");
        viewMatUniformLocation = glGetUniformLocation(shaderProgram, "viewMat");
        projectionMatUniformLocation = glGetUniformLocation(shaderProgram, "projectionMat");
    }
}

void Shader::release()
{
    glDeleteProgram(shaderProgram);
}

unsigned int Shader::getShaderProgram()
{
    return shaderProgram;
}

int Shader::getModelMatUniformLocation()
{
    return modelMatUniformLocation;
}

int Shader::getViewMatUniformLocation()
{
    return viewMatUniformLocation;
}

int Shader::getProjectionMatUniformLocation()
{
    return projectionMatUniformLocation;
}