/**
    Defines the TextureObject struct

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         TextureObject.cpp
    @brief        Definition of the TextureObject struct
*/
#ifndef TEXTURE_OBJECT_CPP
#define TEXTURE_OBJECT_CPP
#include <string>

#include "TEXTURE_TYPE.cpp"

/**
 * Holds information about a texture
 */
struct TextureObject {

    uint32_t            ID;
    TEXTURE_TYPE        type;
    std::string         path;

};
#endif  // TEXTURE_OBJECT_CPP
