/**
	Declares the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.hpp
	@brief		Declaration of the OGLEngine class
*/

#pragma once
#include <iostream>

#include "OGL_STATUS_CODE.hpp"

class OGLEngine {
public:

	/**
		Initializes the OGLEngine and loads dependencies

		@return		OGL_STATUS_CODE	Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE init(void);

private:

	/**
		Initializes the windowing library

		@return		Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE initWindow(void);
	
	/**
		Initializes the OpenGL API

		@return		Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE initOpenGL(void);
	
	/**
		Contains the main loop

		@return		Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE loop(void);

	/**
		Handles cleaning of resources on exit

		@return		Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE clean(void);

};

