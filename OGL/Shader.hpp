/**
    Defines the Shader class

    @author		D3PSI
    @version	0.0.1 02.12.2019

    @file		Shader.hpp
    @brief		Definition of the Shader class
*/
#ifndef SHADER_HPP
#define SHADER_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "Logger.hpp"
#include "OGL_STATUS_CODE.hpp"

class Shader
{
public:

    uint32_t ID;

    /**
        Default constructor
    */
    Shader() = default;

    /**
        Constructor

        @param      vertPath_       The (relative) path to the vertex shader source file
        @param      fragPath_       The (relative) path to the fragment shader source file
        @param      geomPath_       The (relative) path to the geometry shader source file if existent
    */
    Shader(const char* vertPath_, const char* fragPath_, const char* geomPath_ = nullptr);

    /**
        Uses the shader program

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE use(void);

    /**
        Sets a uniform of type boolean in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setBool(const std::string& name_, bool value_) const;

    /**
        Sets a uniform of type int in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setInt(const std::string& name_, int32_t value_) const;

    /**
        Sets a uniform of type float in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setFloat(const std::string& name_, float value_) const;

    /**
        Sets a uniform of type mat4 in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setMat4(const std::string& name_, glm::mat4 value_) const;

    /**
        Sets a uniform of type vec3 in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setVec3(const std::string& name_, glm::vec3 value_) const;

    /**
        Sets a uniform of type vec3 in the shader

        @param      name_       The name of the uniform
        @param      value_      The value to set
    */
    void setVec3(const std::string &name_, float x_, float y_, float z_) const;

    /**
        Default destructor
    */
    ~Shader(void);

};
#endif  // SHADER_HPP
