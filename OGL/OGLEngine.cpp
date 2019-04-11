/**
	Implements the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.cpp
	@brief		Implementation of the OGLEngine class
*/

#include "OGLEngine.hpp"
#include "OGL_STATUS_CODE.hpp"

OGL_STATUS_CODE OGLEngine::init() {

	std::cout << "Hello from OGLEngine!" << std::endl;

	initWindow();
	initOpenGL();
	loop();
	clean();

	return OGL_SC_SUCCESS;

}

OGL_STATUS_CODE OGLEngine::initWindow() {

	return OGL_SC_SUCCESS;

}

OGL_STATUS_CODE OGLEngine::initOpenGL() {

	return OGL_SC_SUCCESS;

}

OGL_STATUS_CODE OGLEngine::loop() {

	return OGL_SC_SUCCESS;

}

OGL_STATUS_CODE OGLEngine::clean() {

	return OGL_SC_SUCCESS;

}
