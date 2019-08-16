/**
    Sets build-options by defining macros

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Version.hpp
    @brief        Set build-options by defining macros
*/
#ifndef VERSION_HPP
#define VERSION_HPP
#include "Makros.hpp"

// Edit configuration here
#define OGL_DEVELOPMENT      // enable this for verbose output
//#define OGL_RELEASE          // enable this for performance
//#define OGL_RELEASE_CONSOLE    // enbable this for performance with console
//#define OGL_NO_LOG             // enable this for full performance

#define OGL_WINDOW_MODE_WINDOWED
//#define OGL_WINDOW_MODE_FULLSCREEN
//#define OGL_WINDOW_MODE_BORDERLESS

//#define WIN_64                // Windows 64-bit
//#define WIN_32              // Windows 32-bit
//#define MACOSX              // macOS X 64-bit
#define LINUX               // Linux 64-bit

//#define OGL_STANDARD_MODEL_LOADING_LIB VKEngineModelLoadingLibTINYOBJ
#define OGL_STANDARD_MODEL_LOADING_LIB VKEngineModelLoadingLibASSIMP

//#define OGL_MULTISAMPLING_NONE
//#define OGL_MULTISAMPLING_x2
//#define OGL_MULTISAMPLING_x4
#define OGL_MULTISAMPLING_x8
//#define OGL_MULTISAMPLING_x16
//#define OGL_MULTISAMPLING_x32
//#define OGL_MULTISAMPLING_x64

// Default values

#ifdef OGL_NO_LOG
    #define OGL_RELEASE
#endif

#if !defined OGL_DEVELOPMENT && !defined OGL_RELEASE && !defined OGL_RELEASE_CONSOLE && !defined OGL_NO_LOG
    #define OGL_DEVELOPMENT
#endif

#if !defined OGL_WINDOW_MODE_WINDOWED && !defined OGL_WINDOW_MODE_FULLSCREEN && !defined OGL_WINDOW_MODE_BORDERLESS
    #define OGL_WINDOW_MODE_BORDERLESS
#endif

#if !defined OGL_MULTISAMPLING_NONE && !defined OGL_MULTISAMPLING_x2 && !defined OGL_MULTISAMPLING_x4 && !defined OGL_MULTISAMPLING_x8 && !defined OGL_MULTISAMPLING_x16 && !defined OGL_MULTISAMPLING_x32 && !defined OGL_MULTISAMPLING_x64
    #define OGL_MULTISAMPLING_NONE
#endif

#if !defined WIN_64 && !defined WIN_32 && !defined MACOSX && !defined LINUX
    #define WIN_64
#endif

#ifdef OGL_RELEASE_CONSOLE
    #define OGL_RELEASE
#endif

#if !defined OGL_DEVELOPMENT && !defined OGL_RELEASE_CONSOLE && defined OGL_RELEASE && (defined WIN_64 || defined WIN_32)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#ifndef NOMINMAX
    #if defined WIN_64 || defined WIN_32
        #define NOMINMAX        // Fixes std::min/std::max/std::clamp error
        #include <Windows.h>
    #endif
#endif // NOMINMAX
#endif  // VERSION_HPP
