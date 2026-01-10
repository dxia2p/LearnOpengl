#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>

#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Turn on exceptions for .failed() and .bad()
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    std::string vShaderContents, fShaderContents;

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream; 
        vShaderStream << vShaderFile.rdbuf(); 
        fShaderStream << fShaderFile.rdbuf();

        vShaderContents = vShaderStream.str();
        fShaderContents = fShaderStream.str();

    } catch(const std::exception& e) {
        std::cerr << "Shader file could not be read: " << e.what() << std::endl;
    }

    const char* vShaderCStr = vShaderContents.c_str();
    const char* fShaderCStr = fShaderContents.c_str();
    int success;
    char log[512];

    unsigned int vShader, fShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderCStr, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, log);
        std::cerr << "Error reading shader at " << vertexPath << ':' << log << std::endl;
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderCStr, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 512, NULL, log);
        std::cerr << "Error reading shader at " << fragmentPath << ':' << log << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cerr << "Error linking shader program: " << log << std::endl;
    }

    this->ID = shaderProgram;

    // Cleanup
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

/*
Shader::~Shader() {
    std::cout << "Destroying shader with ID " << ID << std::endl;
    glDeleteProgram(ID);
}
*/


void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    int uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniform1i(uniformLocation, (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

