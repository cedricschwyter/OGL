/**
	Implements the OGL_STATUS_CODE enumeration

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGL_STATUS_CODE.hpp
	@brief		Implementation of the OGL_STATUS_CODE enumeration
*/
#pragma once

typedef enum OGL_STATUS_CODE {

    OGL_SC_BUFFER_CREATION_ERROR                    = -9,
    OGL_SC_SHADER_CREATION_ERROR                    = -8,
    OGL_SC_VIEWPORT_ERROR                           = -7,
    OGL_SC_GLAD_INITIALIZATION_ERROR                = -6,
    OGL_SC_CLEANUP_ERROR                            = -5,
    OGL_SC_OPENGL_RUNTIME_ERROR                     = -4,
    OGL_SC_OPENGL_ERROR                             = -3,
    OGL_SC_WINDOW_ERROR                             = -2,
	OGL_SC_UNKNOWN_ERROR		                    = -1,
	OGL_SC_SUCCESS				                    = 0,
    OGL_SC_ERROR_CODE_BUFFER_NOT_INITIALIZED        = 1

} OGL_STATUS_CODE;