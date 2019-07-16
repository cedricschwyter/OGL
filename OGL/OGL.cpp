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

}