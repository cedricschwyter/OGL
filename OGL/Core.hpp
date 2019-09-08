/**
	Declares the Core namespace with all its functions

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		Core.hpp
	@brief		Declaration of the Core class
*/

#ifndef OGL_ENGINE_HPP
#define OGL_ENGINE_HPP
#include "Version.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>

#include "OGL_STATUS_CODE.hpp"
#include "Logger.hpp"
#include "LoadingScreen.hpp"
#include "Shader.hpp"
#include "BaseCamera.hpp"
#include "FPSCamera.hpp"
#include "CenterCamera.hpp"
#include "BaseVertex.hpp"
#include "Model.hpp"
#include "SHADER_TYPE.cpp"
#include "ModelInfo.cpp"

namespace ogl {

    namespace core {

        extern Shader*                                                 standardShader;
        extern uint32_t                                                MSAASampleCount;
        extern GLFWwindow*                                             window;
        extern GLFWmonitor*                                            monitor;
        extern int                                                     width;
        extern int                                                     height;
        extern LoadingScreen*                                          loadingScreen;
        extern bool                                                    initialized;
        extern BaseCamera*                                             camera;
        extern std::vector< Model* >                                   models;
        extern std::mutex                                              modelsPushBackMutex;
        extern std::vector< ModelInfo >                                 modelLoadingQueue;
        extern std::vector< std::thread* >                             modelLoadingQueueThreads;

        /**
            Default constructor
        */
        void preInit(void);

        /**
            Initializes the OGLEngine and loads dependencies

            @param      returnCodeAddr_     An OGL_STATUS_CODE pointer to which the return code of this multithreaded function will be written

            @return		OGL_STATUS_CODE	Returns OGL_SC_SUCCESS on success
        */
        void init(OGL_STATUS_CODE* returnCodeAddr_);

        /**
            Adds a model to the model loading queue

            @param      path_           The path to the model
            @param      shader_         The shader to render the model with
            @param      modelMatrix_    The function to invoke that returns the model matrix

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE push(const char* path_, SHADER_TYPE shader_,  glm::mat4 (*modelMatrix_)());

        /**
            Initializes the logger

            @return        Returns LOGGER_SC_SUCCESS on success
            @return        Returns LOGGER_SC_UNKNOWN_ERROR on error
        */
        LOGGER_STATUS_CODE initLogger(void);

        /**
            Initializes the loading screen
        */
        void initLoadingScreen(void);

        /**
            Initializes the windowing library

            @return		Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE initGLFW(void);

        /**
            Initializes the window

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
            Generate shaders

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE generateShaders(void);

        /**
            Generates necessary buffers

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE generateBuffers(void);

        /**
            Initializes OpenGL's viewport

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE initializeViewport(void);

        /**
            Sets pre-render-loop options

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE setup(void);

        /**
            Creates a camera object

            @return     Returns OGL_SC_SUCCESS on success
        */
        OGL_STATUS_CODE createCamera(void);

    }

}
#endif  // OGL_ENGINE_HPP
