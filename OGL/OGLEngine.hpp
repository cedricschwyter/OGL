/**
	Declares the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.hpp
	@brief		Declaration of the OGLEngine class
*/

#pragma once
#include "Version.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#include "OGL_STATUS_CODE.hpp"
#include "Logger.hpp"
#include "LoadingScreen.hpp"
#include "Shader.hpp"

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
    std::vector< float >                    vertices                    = {
    
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    
    };
    Shader*                                 standardShader;
    uint32_t                                VAO;
    uint32_t                                VBO;

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

    /**
        Framebuffer resize callback function for GLFW

        @param         window_        A pointer to a GLFWwindow
        @param         width_        The new width of the GLFWwindow
        @param         height_        The new height of the GLFWwindow
    */
    static void framebufferResizeCallback(GLFWwindow* window_, int width_, int height_);

    /**
        Callback function for GLFW on mouse events

        @param         window_     A pointer to a focused GLFWwindow
        @param         xPos_       The x-component of the mouse's position on screen
        @param         yPos_       The y-component of the mouse's position on screen
    */
    static void mouseMoveCallback(GLFWwindow* window_, double xPos_, double yPos_);

    /**
        Callback function for GLFW on scroll events

        @param         xOff_       The x-component of the scroll wheels offset
        @param         yOff_       The y-component of the scroll wheels offset
    */
    static void mouseScrollCallback(GLFWwindow* window_, double xOff_, double yOff_);

    /**
        Handles keyboard input

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE processKeyboardInput();

    /**
        Renders an image to the screen

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE render(void);

    /**
        Generates necessary buffers

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE generateBuffers(void);

    /**
        Generate OpenGL shader objects

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE generateShaders(void);

    /**
        Initializes OpenGL's viewport

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE initializeViewport(void);

};

