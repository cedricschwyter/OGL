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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    glfwMakeContextCurrent(window);

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

    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    logger::log(EVENT_LOG, "Successfully set framebuffer resize callback");

    glfwSetCursorPosCallback(window, mouseMoveCallback);
    logger::log(EVENT_LOG, "Successfully set cursor position callback");

    glfwSetScrollCallback(window, mouseScrollCallback);
    logger::log(EVENT_LOG, "Successfully set mouse scroll callback");

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::initOpenGL() {

    ASSERT(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD-function-loader for OpenGL", OGL_SC_GLAD_INITIALIZATION_ERROR);
    ASSERT(initializeViewport(), "Failed to initialize viewport", OGL_SC_VIEWPORT_ERROR);
    ASSERT(generateShaders(), "Failed to load shaders", OGL_SC_SHADER_CREATION_ERROR);
    ASSERT(generateBuffers(), "Failed to generate vertex buffers", OGL_SC_BUFFER_CREATION_ERROR);

    if (!initialized) {

        loadingScreen->closeMutex.lock();
        loadingScreen->close = true;
        loadingScreen->closeMutex.unlock();
        glfwShowWindow(window);
        glfwFocusWindow(window);
        initialized = true;

    }

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::loop() {

    while (!glfwWindowShouldClose(window)) {
    
        processKeyboardInput();

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    logger::log(EVENT_LOG, "Terminating GLFW...");
    glfwTerminate();
    logger::log(EVENT_LOG, "Successfully terminated GLFW");

	return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::clean() {

    delete standardShader;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    logger::log(EVENT_LOG, "Successfully destroyed all allocated buffers");

	return ogl::errorCodeBuffer;

}

void OGLEngine::framebufferResizeCallback(GLFWwindow* window_, int width_, int height_) {

    glViewport(0, 0, width_, height_);

}

void OGLEngine::mouseMoveCallback(GLFWwindow* window_, double xPos_, double yPos_) {

    /*auto oglengine = reinterpret_cast< OGLEngine* >(glfwGetWindowUserPointer(window_));
    oglengine->camera->processMouseMovement(xPos_, yPos_);*/

}

void OGLEngine::mouseScrollCallback(GLFWwindow* window_, double xOff_, double yOff_) {

    /*auto oglengine = reinterpret_cast< OGLEngine* >(glfwGetWindowUserPointer(window_));
    oglengine->camera->processMouseScroll(xOff_, yOff_);*/

}

OGL_STATUS_CODE OGLEngine::processKeyboardInput() {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::render() {

    glClearColor(122.0f / 255.0f, 122.0f / 255.0f, 122.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    standardShader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::generateBuffers() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float), 
        (void*)0
        );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::generateShaders() {

    standardShader = new Shader("shaders/standard/shader.vert", "shaders/standard/shader.frag");

    return ogl::errorCodeBuffer;

}

OGL_STATUS_CODE OGLEngine::initializeViewport() {

    glViewport(0, 0, ogl::WIDTH, ogl::HEIGHT);

    return ogl::errorCodeBuffer;

}