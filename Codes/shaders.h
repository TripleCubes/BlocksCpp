#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

class Shader
{
    private:
        unsigned int shaderProgram;
        int modelMatUniformLocation;
        int viewMatUniformLocation;
        int projectionMatUniformLocation;
    
    public:
        void init(std::string vertexShaderPath, std::string fragmentShaderPath, bool hasMvpUniforms);
        unsigned int getShaderProgram();
        int getModelMatUniformLocation();
        int getViewMatUniformLocation();
        int getProjectionMatUniformLocation();
        void release();
};

enum ShaderType {
    VERTEX,
    FRAGMENT
};

extern Shader defaultShader;

unsigned int compileShader(std::string path, ShaderType shader_type);
void linkShaderProgram(unsigned int shaderProgram, std::string vertexShaderPath, std::string fragmentShaderPath);

#endif