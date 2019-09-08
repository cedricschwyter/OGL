/**
    Defines the ModelInfo struct

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         ModelInfo.cpp
    @brief        Definition of the ModelInfo struct
*/
#ifndef MODEL_INFO_CPP
#define MODEL_INFO_CPP
#include <glm/glm.hpp>

#include "SHADER_TYPE.cpp"

/**
    Defines a struct to hold loading information for models
*/
struct ModelInfo {

    const char*                     path;
    SHADER_TYPE                     shader;
    glm::mat4                       (*modelMatrixFunc)();

};
#endif  // MODEL_INFO_CPP
