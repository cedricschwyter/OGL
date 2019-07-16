/**
    Prototypes the ogl namespace

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         OGL.hpp
    @brief        Prototype of the ogl namespace
*/
#pragma once
#include "Version.hpp"

#include "OGLEngine.hpp"
#include "OGL_STATUS_CODE.hpp"


/**
    Prototypes a namespace to prevent global naming conflicts
*/
namespace ogl {

    extern OGL_STATUS_CODE                      errorCodeBuffer;

    extern OGLEngine*                           engine;
    extern const unsigned int                   WIDTH;
    extern const unsigned int                   HEIGHT;
    extern const char*                          TITLE;

    /**
        Initializes the OGLEngine object

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE init(void);

    /**
        Handles main initialization of everything

        @return		Returns OGL_SC_SUCCESS on success
        @return		Returns OGL_SC_UNKNOWN_ERROR on error
    */
    OGL_STATUS_CODE run(void);

}