/**
    Declares the Mesh class

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Mesh.hpp
    @brief        Declaration of the Mesh class
*/
#pragma once
#include <vector>

#include "TextureObject.cpp"
#include "Shader.hpp"
#include "BaseVertex.hpp"

class Mesh
{
public:

    std::vector< BaseVertex >                               vertices;
    std::vector< uint32_t >                                 indices;
    std::vector< TextureObject >                            textures;
    uint32_t                                                VAO;

    /**
        Constructor

        @param      vertices_               Reference to vertex data of mesh
        @param      indices_                Reference to index data of mesh
        @param      textures_               Reference to texture data of mesh
        @param      shader_                 The shaders to render the mesh with
    */
    Mesh(std::vector< BaseVertex >& vertices_, std::vector< uint32_t >& indices_, std::vector< TextureObject >& textures_, Shader shader_);

    /**
        Binds the vertex and index data for command buffer recording and executes the draw call
    */
    void draw(void);

    /**
        Default destructor
    */
    ~Mesh(void);

private:

    uint32_t VBO, EBO;
    Shader shader;

};

