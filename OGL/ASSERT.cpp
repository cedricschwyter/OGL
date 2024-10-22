/**
    Implements the ASSERT function

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         ASSERT.cpp
    @brief        Implementation of the ASSERT function
*/
#ifndef ASSERT_CPP
#define ASSERT_CPP
#include <iostream>

#include "OGL.hpp"
#include "Logger.hpp"

/**
    Checks functions for a returncode other than 0 and throws an error

    @param         val_    Value to be tested
    @param         msg_    Error message that will get logged
    @param         ret_    Return code

    @return        Returns ret_ if val_ is not 0
    @return        Returns val_ if val_ is 0
*/
inline int ASSERT(int val_, const char* msg_, int ret_) {

    static std::mutex assertMutex;

    if (val_ != 0) {

        assertMutex.lock();
        ogl::errorCodeBuffer = static_cast< OGL_STATUS_CODE >(ret_);
        assertMutex.unlock();

        logger::log(ERROR_LOG, msg_);

        return ret_;

    }
    else {

        assertMutex.lock();
        ogl::errorCodeBuffer = static_cast< OGL_STATUS_CODE >(val_);
        assertMutex.unlock();

        return val_;

    }

}
#endif  // ASSERT_CPP