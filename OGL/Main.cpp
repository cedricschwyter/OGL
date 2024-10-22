/**
	Implements the main entry point for the OGLEngine

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		Main.cpp
	@brief		Implementation of the OpenGL-part for my Vulkan vs. OpenGL comparison (Maturaarbeit)
*/
#include "OGL.hpp"

/**
    Returns the model matrix for the nanosuit model  
  
    @return     Returns a glm::mat4
*/
glm::mat4 nanosuit() {

    glm::mat4 model;
    model           = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model           = glm::scale(model, glm::vec3(0.02f));
	
    return model;

}

/**
	Entry point for the application
*/
int main() {

    ogl::init();

    ogl::push("res/models/nanosuit/nanosuit.obj", ST_STANDARD, &nanosuit);

	return ogl::run();

}