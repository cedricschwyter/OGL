/**
	Implements the OGLEngine class

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		OGLEngine.cpp
	@brief		Implementation of the OGLEngine class
*/

#include "OGLEngine.hpp"
#include "OGL.hpp"
#include "ASSERT.cpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void OGLEngine::init(OGL_STATUS_CODE* returnCodeAddr_) {

    logger::log(START_LOG, "Initializing...");
    logger::log(EVENT_LOG, "Initializing loading screen...");
    initLoadingScreen();
    ASSERT(initWindow(), "Window initialization error", OGL_SC_WINDOW_ERROR);
    ASSERT(initOpenGL(), "OpenGL initialization error", OGL_SC_OPENGL_ERROR);
    ASSERT(loop(), "OpenGL runtime error", OGL_SC_OPENGL_RUNTIME_ERROR);
    ASSERT(clean(), "Application cleanup error", OGL_SC_CLEANUP_ERROR);
    logger::log(START_LOG, "Shutting down...");

    OGL_STATUS_CODE* returnCode;
    returnCode          = returnCodeAddr_;
    *returnCode         = ogl::errorCodeBuffer;

}

void OGLEngine::initLoadingScreen() {

    loadingScreen = new LoadingScreen();

    logger::log(EVENT_LOG, "Starting loading screen thread...");
    std::thread t0([=]() {

        loadingScreen->loop();
        logger::log(EVENT_LOG, "Stopping loading screen thread...");

        });
    t0.detach();

}

LOGGER_STATUS_CODE OGLEngine::initLogger() {

    return logger::init();

}

OGL_STATUS_CODE OGLEngine::initWindow() {

    logger::log(EVENT_LOG, "Initializing window...");
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

#ifdef VK_WINDOW_MODE_FULLSCREEN
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(
        mode->width,
        mode->height,
        vk::TITLE,
        monitor,
        nullptr
    );
#endif
#if defined VK_WINDOW_MODE_WINDOWED
    window = glfwCreateWindow(
        ogl::WIDTH,
        ogl::HEIGHT,
        ogl::TITLE,
        nullptr,
        nullptr
    );

    glfwSetWindowPos(
        window,
        mode->width / 2 - ogl::WIDTH / 2,
        mode->height / 2 - ogl::HEIGHT / 2
    );
#endif
#if defined VK_WINDOW_MODE_BORDERLESS || defined VK_WINDOW_MODE_UNDEFINED
    window = glfwCreateWindow(
        mode->width,
        mode->height,
        vk::TITLE,
        monitor,
        nullptr
    );
#endif

    GLFWimage windowIcon[1];
    windowIcon[0].pixels = stbi_load(
        "res/textures/loading_screen/infinity.jpg",
        &windowIcon[0].width,
        &windowIcon[0].height,
        0,
        STBI_rgb_alpha
        );

    glfwSetWindowIcon(window, 1, windowIcon);
    stbi_image_free(windowIcon[0].pixels);
    logger::log(EVENT_LOG, "Successfully initialized window");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(window, this);
    logger::log(EVENT_LOG, "Successfully set GLFW window user pointer");

    /*glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    logger::log(EVENT_LOG, "Successfully set framebuffer resize callback");

    glfwSetCursorPosCallback(window, mouseMoveCallback);
    logger::log(EVENT_LOG, "Successfully set cursor position callback");

    glfwSetScrollCallback(window, mouseScrollCallback);
    logger::log(EVENT_LOG, "Successfully set mouse scroll callback");*/

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::initOpenGL() {

    if (!initialized) {

        loadingScreen->closeMutex.lock();
        loadingScreen->close = true;
        loadingScreen->closeMutex.unlock();
        //glfwShowWindow(window);
        //glfwFocusWindow(window);
        initialized = true;

    }

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::loop() {

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::clean() {

	return ogl::errorCodeBuffer;

}
