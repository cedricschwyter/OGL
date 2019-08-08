/**
    Defines the TEXTURE_TYPE struct

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         TEXTURE_TYPE.cpp
    @brief        Definition of the TEXTURE_TYPE struct
*/
#ifndef TEXTURE_TYPE_CPP
#define TEXTURE_TYPE_CPP

/**
 * Enumeration to differenciate between the different types of textures
 */
typedef enum TEXTURE_TYPE {

    TT_HEIGHT,
    TT_NORMAL,
    TT_SPECULAR,
    TT_DIFFUSE,
    TT_STANDARD

} TEXTURE_TYPE;
#endif  // TEXTURE_TYPE_CPP
