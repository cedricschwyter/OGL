/**
	Implements the main entry point for the OGLEngine

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		Main.cpp
	@brief		Implementation of the OpenGL-part for my Vulkan vs. OpenGL comparison (Maturaarbeit)
*/
#include <iostream>

#include "OGLEngine.hpp"
#include "OGL_STATUS_CODE.hpp"

/**
	Prototypes a namespace to prevent global naming conflicts
*/
namespace ogl {

	/**
		Handles main initialization of everything

		@return		Returns OGL_SC_SUCCESS on success
		@return		Returns OGL_SC_UNKNOWN_ERROR on error
	*/
	OGL_STATUS_CODE init(void);

}

namespace ogl {

	OGLEngine engine;

	OGL_STATUS_CODE init() {
	
		try {
		
			return engine.init();
		
		}
		catch (const std::exception& e) {
		
			std::cerr << e.what() << std::endl;

			return OGL_SC_UNKNOWN_ERROR;
		
		}
	
	}

}

/**
	Entry point for the application
*/
int main() {

	std::cout << "Hello from OGL!" << std::endl;

	return 0;

}