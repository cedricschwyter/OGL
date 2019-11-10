/**
	Implements the Core namespace

	@author		D3PSI
	@version	0.0.1 02.12.2019

	@file		Core.cpp
	@brief		Implementation of the Core namespace
*/

#include "Core.hpp"
#include "OGL.hpp"
#include "ASSERT.cpp"
#include "ModelInfo.cpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ogl {

    namespace core {

        Shader*                                                 standardShader;
        uint32_t                                                MSAASampleCount;
        GLFWwindow*                                             window;
        GLFWmonitor*                                            monitor;
        int                                                     width                       = ogl::WIDTH;
        int                                                     height                      = ogl::HEIGHT;
        LoadingScreen*                                          loadingScreen               = nullptr;
        bool                                                    initialized                 = false;
        BaseCamera*                                             camera;
        std::vector< Model* >                                   models;
        std::mutex                                              modelsPushBackMutex;
        std::vector< ModelInfo >                                modelLoadingQueue;
        std::vector< std::thread* >                             modelLoadingQueueThreads;

        void preInit() {

            ASSERT(initLogger(), "Logger initialization error", LOGGER_SC_UNKNOWN_ERROR);
            logger::log(START_LOG, "Initializing...");

        }

        void init(OGL_STATUS_CODE* returnCodeAddr_) {

            logger::log(EVENT_LOG, "Initializing loading screen...");
            initLoadingScreen();
            ASSERT(initGLFW(), "GLFW initialization error", OGL_SC_WINDOW_ERROR);
            ASSERT(initWindow(), "Window initialization error", OGL_SC_WINDOW_ERROR);
            ASSERT(initOpenGL(), "OpenGL initialization error", OGL_SC_OPENGL_ERROR);
            ASSERT(loop(), "OpenGL runtime error", OGL_SC_OPENGL_RUNTIME_ERROR);
            ASSERT(clean(), "Application cleanup error", OGL_SC_CLEANUP_ERROR);
            logger::log(START_LOG, "Shutting down...");

            OGL_STATUS_CODE* returnCode;
            returnCode          = returnCodeAddr_;
            *returnCode         = ogl::errorCodeBuffer;

        }

        void initLoadingScreen() {

            loadingScreen = new LoadingScreen();

            logger::log(EVENT_LOG, "Starting loading screen thread...");
            std::thread t0(&LoadingScreen::loop, loadingScreen);
            t0.detach();

        }

        LOGGER_STATUS_CODE initLogger() {

            return logger::init();

        }

        OGL_STATUS_CODE initGLFW() {

            logger::log(EVENT_LOG, "Initializing window...");
        #ifdef OGL_MULTISAMPLING_NONE
            MSAASampleCount = 1;
        #elif defined OGL_MULTISAMPLING_x2
            MSAASampleCount = 2;
        #elif defined OGL_MULTISAMPLING_x4
            MSAASampleCount = 4;
        #elif defined OGL_MULTISAMPLING_x8
            MSAASampleCount = 8;
        #elif defined OGL_MULTISAMPLING_x16
            MSAASampleCount = 16;
        #elif defined OGL_MULTISAMPLING_x32
            MSAASampleCount = 32;
        #elif defined OGL_MULTISAMPLING_x64
            MSAASampleCount = 64;
        #endif

            glfwInit();

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifndef OGL_MULTISAMPLING_NONE
            glfwWindowHint(GLFW_SAMPLES, MSAASampleCount);
        #endif
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
            glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE initWindow() {

            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        #ifdef OGL_WINDOW_MODE_FULLSCREEN
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            window = glfwCreateWindow(
                mode->width,
                mode->height,
                ogl::TITLE,
                monitor,
                nullptr
            );
        #endif
        #if defined OGL_WINDOW_MODE_WINDOWED
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
        #if defined OGL_WINDOW_MODE_BORDERLESS
            window = glfwCreateWindow(
                mode->width,
                mode->height,
                ogl::TITLE,
                monitor,
                nullptr
            );
        #endif

            glfwMakeContextCurrent(window);
            glfwSwapInterval(0);

            GLFWimage windowIcon[1];
            windowIcon[0].pixels = stbi_load(
                "res/textures/application/minimalist-lion-wallpaper-cropped.png",
                &windowIcon[0].width,
                &windowIcon[0].height,
                0,
                STBI_rgb_alpha
                );

            glfwSetWindowIcon(window, 1, windowIcon);
            stbi_image_free(windowIcon[0].pixels);
            logger::log(EVENT_LOG, "Successfully initialized window");

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
            logger::log(EVENT_LOG, "Successfully set framebuffer resize callback");

            glfwSetCursorPosCallback(window, mouseMoveCallback);
            logger::log(EVENT_LOG, "Successfully set cursor position callback");

            glfwSetScrollCallback(window, mouseScrollCallback);
            logger::log(EVENT_LOG, "Successfully set mouse scroll callback");

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE initOpenGL() {

            ASSERT(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD-function-loader for OpenGL", OGL_SC_GLAD_INITIALIZATION_ERROR);
            ASSERT(initializeViewport(), "Failed to initialize viewport", OGL_SC_VIEWPORT_ERROR);
            ASSERT(generateShaders(), "Failed to generate shaders", OGL_SC_SHADER_CREATION_ERROR);
            ASSERT(generateBuffers(), "Failed to generate vertex buffers", OGL_SC_BUFFER_CREATION_ERROR);
            ASSERT(createCamera(), "Failed to create camera", OGL_SC_CAMERA_CREATION_ERROR);

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

        OGL_STATUS_CODE loop() {

            double                    lastTime = glfwGetTime();

            setup();

            while (!glfwWindowShouldClose(window)) {
            
                static double       pastTime = 0;
                static float        nbFrames = 0;
                static float        maxfps = 0;
                double              currentTime = glfwGetTime();
                double              deltaTime = currentTime - pastTime;

                pastTime = currentTime;

                nbFrames++;
                float seconds = 10.0f;

                if (currentTime - lastTime >= 1.0 && nbFrames > maxfps) {

                    maxfps = nbFrames;

                }

                if (currentTime - lastTime >= seconds) {
        #ifndef OGL_NO_LOG
                    std::string fps = "Average FPS (last " + std::to_string(seconds) + " seconds):    %f\t";
                    std::string frametime = "Average Frametime (last " + std::to_string(seconds) + " seconds):    %f ms\t";
                    std::string maxFPS = "Max FPS:    %f\n";

                    printf(fps.c_str(), double(nbFrames / seconds));
                    printf(frametime.c_str(), double((1000.0 * seconds) / nbFrames));
                    printf(maxFPS.c_str(), double(maxfps / seconds));
        #endif
                    nbFrames = 0;
                    lastTime += seconds;

                }

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

        OGL_STATUS_CODE clean() {

            for (auto model : models) {

                delete model;

            }

            delete camera;
            logger::log(EVENT_LOG, "Successfully destroyed camera");

            return ogl::errorCodeBuffer;

        }

        void framebufferResizeCallback(GLFWwindow* window_, int width_, int height_) {

            width = width_;
            height = height_;
            glViewport(0, 0, width_, height_);

        }

        void mouseMoveCallback(GLFWwindow* window_, double xPos_, double yPos_) {

            core::camera->processMouseMovement(xPos_, yPos_);

        }

        void mouseScrollCallback(GLFWwindow* window_, double xOff_, double yOff_) {

            core::camera->processMouseScroll(xOff_, yOff_);

        }

        OGL_STATUS_CODE processKeyboardInput() {

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);

            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

                static double start = glfwGetTime() - 1.0;      // -1.0 prevents bug for first time switch
                double now = glfwGetTime();
                static bool pressed = false;

                if (now - start > 0.5) {

                    delete camera;
                    if (pressed) {

                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        camera = new FPSCamera();
                        pressed = false;
                    }
                    else {

                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        camera = new CenterCamera(ogl::centerCameraTarget, 5.0f);
                        pressed = true;

                    }
                    start = glfwGetTime();

                }

            }

            camera->processKeyboardInput(window);
            ogl::keyboardInputCallback(window);

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE setup() {

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        #ifndef OGL_MULTISAMPLING_NONE
            glEnable(GL_MULTISAMPLE);
        #endif

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE render() {

            glClearColor(122.0f / 255.0f, 122.0f / 255.0f, 122.0f / 255.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 view = camera->getViewMatrix();

            glm::mat4 projection;
            projection = glm::perspective(static_cast< float >(glm::radians(camera->fov)), width / static_cast< float >(height), 0.1f, 100.0f);

            glm::vec3 lightPos = glm::vec3(static_cast< float >(glm::cos(glfwGetTime())), 0.0f, static_cast< float >(glm::sin(glfwGetTime())));

            for (auto mod : models) {
            
                glm::mat4 model = mod->getModelMatrix();

                mod->shader.use();
                mod->shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                mod->shader.setVec3("lightPos", lightPos);
                mod->shader.setVec3("viewPos", camera->camPos);
                mod->shader.setMat4("model", model);
                mod->shader.setMat4("view", view);
                mod->shader.setMat4("projection", projection);
                mod->draw();
            
            }

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE generateBuffers() {

            for (auto info : modelLoadingQueue) {

                Shader* shader = nullptr;
                if (info.shader == ST_STANDARD) {

                    shader = standardShader;

                }

                Model* model = new Model(info.path, *shader, info.modelMatrixFunc);

                std::scoped_lock< std::mutex > lock(modelsPushBackMutex);
                models.push_back(model);
                logger::log(EVENT_LOG, "Successfully loaded model at " + std::string(info.path));

            }

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE generateShaders() {

            standardShader = new Shader("shaders/standard/shader.vert", "shaders/standard/shader.frag");
            logger::log(EVENT_LOG, "Successfully loaded shaders");

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE initializeViewport() {

            glViewport(0, 0, width, height);

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE createCamera() {

            camera = new FPSCamera();
            logger::log(EVENT_LOG, "Successfully created camera");

            return ogl::errorCodeBuffer;

        }

        OGL_STATUS_CODE push(const char* path_, SHADER_TYPE shader_, glm::mat4 (*modelMatrix_)()) {

            modelLoadingQueue.push_back({ path_, shader_, modelMatrix_ });

            return ogl::errorCodeBuffer;

        }

    }

}
