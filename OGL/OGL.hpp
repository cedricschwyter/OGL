/**
    Prototypes the ogl namespace

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         OGL.hpp
    @brief        Prototype of the ogl namespace
*/
#ifndef OGL_HPP
#define OGL_HPP
#include "Version.hpp"

#include <glad/glad.h>

#include "Core.hpp"
#include "OGL_STATUS_CODE.hpp"

/**
    Prototypes a namespace to prevent global naming conflicts
*/
namespace ogl {

    extern OGL_STATUS_CODE                      errorCodeBuffer;

    extern const unsigned int                   WIDTH;
    extern const unsigned int                   HEIGHT;
    extern const char*                          TITLE;

    // Starting/Default camera state values
    extern const double                         YAW;
    extern const double                         PITCH;
    extern const double                         ROLL;
    extern const double                         SPEED;
    extern const double                         SENS;
    extern const double                         FOV;
    extern glm::vec3                            centerCameraTarget;
    extern std::mutex                           bufferGenerationMutex;

    extern void                                 (*kipCallback)(GLFWwindow*);

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

    /**
        Makes the console invisible
    */
    void hideConsole(void);

    /**
        Makes the console visible
    */
    void showConsole(void);

    /**
        Checks whether the console window is visible at the moment

        @return        Returns true if the console window is visible
        @return        Returns false if the console window is not visible
    */
    bool isConsoleVisible(void);

    /**
        Loads a file from disc and returns its contents in a char array

        @param         filePath_        The (relative) file path to the desired file

        @return        Returns an std::vector< char > containing the binary content of the specified input file
    */
    const std::vector< char > loadFile(const std::string& filePath_);

    /**
        Adds a model to the model loading queue

        @param      path_               The path to the model
        @param      shader_             The shader to render the model with
        @param      modelMatrix_        The function to invoke that returns the model matrix

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE push(const char* path_, SHADER_TYPE shader_, glm::mat4 (*modelMatrix_)());

    /**
        Calls the keyboard input callback function defined by the user

        @param      window_     A pointer to the GLFWwindow of the application
    */
    void keyboardInputCallback(GLFWwindow* window_);

    /**
        Sets the keyboard input callback

        @param      kipCallback_    The functionpointer to the callback function
    */
    void setKeyboardInputCallback(void (*kipCallback_)(GLFWwindow* window_));

}
#endif  // OGL_HPP
