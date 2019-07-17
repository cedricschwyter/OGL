/**
    Implements the ogl namespace

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         OGL.cpp
    @brief        Prototype of the ogl namespace
*/
#include "OGL.hpp"
#include "ASSERT.cpp"
#include "OGL_STATUS_CODE.hpp"


namespace ogl {

    OGL_STATUS_CODE             errorCodeBuffer                 = OGL_SC_ERROR_CODE_BUFFER_NOT_INITIALIZED;

    OGLEngine*                  engine;
    const unsigned int          WIDTH                           = 1280;
    const unsigned int          HEIGHT                          = 720;
    const char*                 TITLE                           = "OGL by D3PSI";

    OGL_STATUS_CODE init() {
    
        engine = new OGLEngine();
        ASSERT(engine->initLogger(), "Logger initialization error", LOGGER_SC_UNKNOWN_ERROR);
        
        return OGL_SC_SUCCESS;
    
    }

    OGL_STATUS_CODE run() {

        try {

            OGL_STATUS_CODE* returnAddr = new OGL_STATUS_CODE();
            std::thread t0(&OGLEngine::init, engine, returnAddr);
            t0.join();

            OGL_STATUS_CODE retCode = *returnAddr;
            delete returnAddr;

            return retCode;

        }
        catch (std::exception& e) {

            logger::log(ERROR_LOG, e.what());

            return errorCodeBuffer;

        }

    }

    void hideConsole() {
#if defined WIN_64 || defined WIN_32
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

    }

    void showConsole() {
#if defined WIN_64 || defined WIN_32
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
    }

    bool isConsoleVisible() {
#if defined WIN_64 || defined WIN_32
        return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
#else
        return false;
#endif
    }

    const std::vector< char > loadFile(const std::string& filePath_) {

        logger::log(EVENT_LOG, "Loading file at '" + filePath_ + "'");

        std::ifstream file(filePath_, std::ios::ate | std::ios::binary);        // Start reading at end of file --> determine the buffer size needed

        if (!file.is_open()) {

            logger::log(ERROR_LOG, "Failed to load file at '" + filePath_ + "'");

        }

        size_t bufferSize = (size_t)file.tellg();        // Find read position and thus necessary buffer size
        std::vector< char > buffer(bufferSize);

        file.seekg(0);        // Translate back to the beginning of the file
        file.read(buffer.data(), bufferSize);
        file.close();

        return buffer;

    }

}