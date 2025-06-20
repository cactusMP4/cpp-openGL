//
// Created by cactusMP4 on 15.06.2025.
//

#include "Shader.h"

#include <iostream>
#include <fstream>

GLuint compileShader(const GLenum shaderType, const std::string& shaderSource) {
    const GLuint ShaderID = glCreateShader(shaderType);
    const GLchar* ShaderSrc = shaderSource.c_str();
    glShaderSource(ShaderID, 1, &ShaderSrc, nullptr);
    glCompileShader(ShaderID);

    GLint success;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(ShaderID, 1024, &log_length, message);

        const std::string shaderTypeString = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
        std::cout << "failed to compile "<< shaderTypeString <<" shader: "<< std::endl << message << std::endl;

        glDeleteShader(ShaderID);
        return 0;
    }

    return ShaderID;
}

Shader::Shader(const std::string& filepath) {
    std::string vertexSrc, fragmentSrc;
    std::string shaderFileSrc;

    std::ifstream shaderFile(filepath);

    bool readingVertex = true;
    while (std::getline(shaderFile, shaderFileSrc)) {
        if (shaderFileSrc == "#type vertex") {
            readingVertex = true;
        } else if (shaderFileSrc == "#type fragment") {
            readingVertex = false;
        } else {
            if (readingVertex) {
                vertexSrc += shaderFileSrc + "\n";
            } else {
                fragmentSrc += shaderFileSrc + "\n";
            }
        }
    }

    const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);


    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLsizei log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        GLchar message[1024];
        glGetProgramInfoLog(program, 1024, &log_length, message);

        std::cout << "failed to link shaders: "<< std::endl << message << std::endl;
    }
}
GLuint Shader::getProgram() const {
    return this->program;
}
