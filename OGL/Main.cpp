/**
	Implements the main entry point for the OGLEngine

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		Main.cpp
	@brief		Implementation of the OpenGL-part for my Vulkan vs. OpenGL comparison (Maturaarbeit)
*/
#include "OGL.hpp"

/**
	Entry point for the application
*/
int main() {

    ogl::init();

    ogl::push("res/models/Mountain_Bike/OBJ/Mountain_Bike.obj", ST_STANDARD);

	return ogl::run();

}