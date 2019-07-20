/**
    Declares the Model class

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Model.hpp
    @brief        Declaration of the Model class
*/
#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

class Model
{
public:

    std::vector< Mesh* >                                        meshes;

    /**
        Constructor

        @param      path_           The path to the .obj-file$
        @param      shader_         The shader to draw the model with
    */
    Model(const char* path_, Shader shader_);

    /**
        Draws the model
    */
    void draw(void);

    /**
        Default destructor
    */
    ~Model(void);

private:

    std::string                                                 directory;
    Shader                                                      shader;
    std::vector< TextureObject >                                texturesLoaded;

    /**
        Handles and coordinates all loading actions for the specified file, using ASSIMP

        @param      path_       The path to the .obj-file to load

        @return     Returns OGL_SC_SUCCESS on success
    */
    OGL_STATUS_CODE loadOBJASSIMP(const char* path_);

    /**
        Helper function for ASSIMP's node-loading system

        @param      node_       A pointer to ASSIMP's node
        @param      scene_      A pointer to ASSIMP's scene
    */
    void processASSIMPNode(aiNode* node_, const aiScene* scene_);

    /**
        Helper function for ASSIMP's mesh-loading system

        @param      mesh_       A pointer to ASSIMP's mesh
        @param      scene_      A pointer to ASSIMP's scene

        @return     Returns a (parsed) Mesh-object pointer that VKEngine can work with
    */
    Mesh* processASSIMPMesh(aiMesh* mesh_, const aiScene* scene_);

    /**
        Helper function for ASSIMP's texture loading system

        @param      material_       A pointer to ASSIMP's material
        @param      type_           ASSIMP texture type flags
        @param      typeID_         Own TEXTURE_TYPE type enumeration

        @return     Returns an std::vector of TextureObjects and descriptors
    */
    std::vector< TextureObject > loadASSIMPMaterialTextures(aiMaterial* material_, aiTextureType type_, TEXTURE_TYPE typeID_);

    /**
        Loads a texture from a file

        @param      path_           The path (actually just the filename) to the file
        @param      directory_      A reference to a string containing the directory path
        @param      gamma_          Is the texture file already gamma corrected?

        @return     Returns an index for OpenGLs texture
    */
    uint32_t textureFromFile(const char* path_, const std::string& directory_, bool gamma_ = false);

};

