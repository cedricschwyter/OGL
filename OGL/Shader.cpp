/**
    Implements the Shader class

    @author		D3PSI
    @version	0.0.1 02.12.2019

    @file		Shader.cpp
    @brief		Implementation of the Shader class
*/
#include "Shader.hpp"
#include "OGL.hpp"


Shader::Shader(const char* vertPath_, const char* fragPath_, const char* geomPath_) {

    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

        vShaderFile.open(vertPath_);
        fShaderFile.open(fragPath_);
        if (geomPath_ != nullptr) gShaderFile.open(geomPath_);
        std::stringstream vShaderStream, fShaderStream, gShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        if (geomPath_ != nullptr) gShaderStream << gShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();
        if (geomPath_ != nullptr) gShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (geomPath_ != nullptr) geometryCode = gShaderStream.str();

    }
    catch (std::ifstream::failure e) {

        logger::log(ERROR_LOG, "Failed to read file");

    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geomPath_ != nullptr ? geometryCode.c_str() : nullptr;

    uint32_t vertex, fragment, geometry;
    int32_t success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
    
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        logger::log(ERROR_LOG, "Failed to compile shader at " + std::string(vertPath_) + " : " + std::string(infoLog));
    
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {

        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        logger::log(ERROR_LOG, "Failed to compile shader at " + std::string(fragPath_) + " : " + std::string(infoLog));

    }

    if (geomPath_ != nullptr) {
    
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if (!success) {

            glGetShaderInfoLog(geometry, 512, nullptr, infoLog);
            logger::log(ERROR_LOG, "Failed to compile shader at " + std::string(geomPath_) + " : " + std::string(infoLog));

        }
    
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glAttachShader(ID, geometry);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {

            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            logger::log(ERROR_LOG, "Failed to link shader: " + std::string(infoLog));

        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteShader(geometry);

    }
    else {
    
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {

            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            logger::log(ERROR_LOG, "Failed to link shader: " + std::string(infoLog));

        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    
    }

}

OGL_STATUS_CODE Shader::use() {

    glUseProgram(ID);

    return ogl::errorCodeBuffer;

}

void Shader::setBool(const std::string& name_, bool value_) const {

    glUniform1i(glGetUniformLocation(ID, name_.c_str()), (int)value_);

}

void Shader::setInt(const std::string& name_, int32_t value_) const {

    glUniform1i(glGetUniformLocation(ID, name_.c_str()), value_);

}

void Shader::setFloat(const std::string& name_, float value_) const {

    glUniform1f(glGetUniformLocation(ID, name_.c_str()), value_);

}

void Shader::setMat4(const std::string& name_, glm::mat4 value_) const {

    glUniformMatrix4fv(glGetUniformLocation(ID, name_.c_str()), 1, GL_FALSE, glm::value_ptr(value_));

}

Shader::~Shader() {



}
