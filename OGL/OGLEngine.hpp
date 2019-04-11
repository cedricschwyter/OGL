/**
	Declares the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.hpp
	@brief		Declaration of the OGLEngine class
*/

#pragma once
#include "OGL_STATUS_CODE.hpp"

class OGLEngine {
public:

	/**
		Initializes the application and loads dependencies

		@return		OGL_STATUS_CODE	Returns OGL_SC_SUCCESS on success
	*/
	OGL_STATUS_CODE init(void);
};

