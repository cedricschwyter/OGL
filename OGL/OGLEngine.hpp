/**
	Declares the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.hpp
	@brief		Declaration of the OGLEngine class
*/

#pragma once
#include "Version.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>

#include "OGL_STATUS_CODE.hpp"
#include "Logger.hpp"
#include "LoadingScreen.hpp"

class OGLEngine {
public:

    /**
        Default constructor
    */
    OGLEngine(void) = default;

    /**
        Default destructor
    */
    ~OGLEngine(void) = default;

	/**
		Initializes the OGLEngine and loads dependencies

        @param      returnCodeAddr_     An OGL_STATUS_CODE pointer to which the return code of this multithreaded function will be written

		@return		OGL_STATUS_CODE	Returns OGL_SC_SUCCESS on success
	*/
	void init(OGL_STATUS_CODE* returnCodeAddr_);

    /**
        Initializes the logger

        @return        Returns LOGGER_SC_SUCCESS on success
        @return        Returns LOGGER_SC_UNKNOWN_ERROR on error
    */
    LOGGER_STATUS_CODE initLogger(void);

private:

    GLFWwindow*                             window;
    GLFWmonitor*                            monitor;

    LoadingScreen*                          loadingScreen               = nullptr;
    bool                                    initialized                 = false;

    /**
        Initializes the loading screen
    */
    void initLoadingScreen(void);

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

