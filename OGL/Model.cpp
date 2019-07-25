/**
    Implementation the Model class

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Model.cpp
    @brief        Implementation of the Model class
*/
#include "Model.hpp"
#include "OGL.hpp"
#include "ASSERT.cpp"

#include <stb_image.h>


Model::Model(const char* path_, Shader shader_) : shader(shader_) {

    OGL_STATUS_CODE result = loadOBJASSIMP(path_);

    ASSERT(result, "Error loading model using ASSIMP", OGL_SC_RESOURCE_LOADING_ERROR);

}

void Model::draw() {

    for (uint32_t i = 0; i < meshes.size(); i++) {
    
        meshes[i]->draw();
    
    }

}

OGL_STATUS_CODE Model::loadOBJASSIMP(const char* path_) {

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path_, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

        std::string error = importer.GetErrorString();
        logger::log(ERROR_LOG, "Error loading model using ASSIMP: " + error);

        return OGL_SC_MODEL_LOADING_ERROR_ASSIMP;

    }

    directory = (std::string(path_)).substr(0, (std::string(path_)).find_last_of("/"));
    processASSIMPNode(scene->mRootNode, scene);

    return ogl::errorCodeBuffer;

}

void Model::processASSIMPNode(aiNode* node_, const aiScene* scene_) {

    // Process each of the meshes using iteration
    for (uint32_t i = 0; i < node_->mNumMeshes; i++) {
    
        aiMesh* mesh = scene_->mMeshes[node_->mMeshes[i]];
        meshes.push_back(processASSIMPMesh(mesh, scene_));
    
    }

    // Process each of ASSIMP's node's children using recursion in the same way
    for (uint32_t i = 0; i < node_->mNumChildren; i++) {
    
        processASSIMPNode(node_->mChildren[i], scene_);
    
    }

}

Mesh* Model::processASSIMPMesh(aiMesh* mesh_, const aiScene* scene_) {

    std::vector< BaseVertex >                                vertices;
    std::vector< uint32_t >                                  indices;

    std::unordered_map< BaseVertex, uint32_t >               uniqueVertices         = {};

    for (uint32_t i = 0; i < mesh_->mNumVertices; i++) {

        BaseVertex vertex = {};

        glm::vec3 vector;
        vector.x            = mesh_->mVertices[i].x;
        vector.y            = mesh_->mVertices[i].y;
        vector.z            = mesh_->mVertices[i].z;
        vertex.pos          = vector;

        if (mesh_->HasNormals()) {

            vector.x            = mesh_->mNormals[i].x;
            vector.y            = mesh_->mNormals[i].y;
            vector.z            = mesh_->mNormals[i].z;
            vertex.nor          = vector;

        }

        if (mesh_->mTextureCoords[0]) {     // Does the mesh contain texture coordinates?
        
            glm::vec2 vec;
            vec.x           = mesh_->mTextureCoords[0][i].x;
            vec.y           = mesh_->mTextureCoords[0][i].y;
            vertex.tex      = vec;

        }
        else {

            vertex.tex      = glm::vec2(0.0f, 0.0f);
        
        }

        if(mesh_->HasTangentsAndBitangents()) {

            vector.x            = mesh_->mTangents[i].x;
            vector.y            = mesh_->mTangents[i].y;
            vector.z            = mesh_->mTangents[i].z;
            vertex.tan          = vector;

            vector.x            = mesh_->mBitangents[i].x;
            vector.y            = mesh_->mBitangents[i].y;
            vector.z            = mesh_->mBitangents[i].z;
            vertex.bit          = vector;

        }

        if (uniqueVertices.count(vertex) == 0) {

            uniqueVertices[vertex] = static_cast< uint32_t >(vertices.size());
            vertices.push_back(vertex);


        }

        indices.push_back(uniqueVertices[vertex]);
    
    }

    std::vector< TextureObject > textures;

    aiMaterial* material = scene_->mMaterials[mesh_->mMaterialIndex];
    
    std::vector< TextureObject > diffuseMaps = loadASSIMPMaterialTextures(material, aiTextureType_DIFFUSE, TT_DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector< TextureObject > specularMaps = loadASSIMPMaterialTextures(material, aiTextureType_SPECULAR, TT_SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector< TextureObject > normalMaps = loadASSIMPMaterialTextures(material, aiTextureType_NORMALS, TT_NORMAL);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector< TextureObject > heightMaps = loadASSIMPMaterialTextures(material, aiTextureType_HEIGHT, TT_HEIGHT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return new Mesh(
        vertices, 
        indices, 
        textures,
        shader
        );

}

std::vector< TextureObject > Model::loadASSIMPMaterialTextures(aiMaterial* material_, aiTextureType type_, TEXTURE_TYPE typeID_) {

    std::vector< TextureObject > textures;

    for (uint32_t i = 0; i < material_->GetTextureCount(type_); i++) {

        aiString texturePath;
        material_->GetTexture(type_, i, &texturePath);

        bool skip = false;

        for (uint32_t j = 0; j < texturesLoaded.size(); j++) {

            if (std::strcmp(texturesLoaded[j].path.data(), texturePath.C_Str()) == 0) {

                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;

            }

        }

        if (!skip) {

            logger::log(EVENT_LOG, "Loading texture at: " + directory + '/' + texturePath.C_Str());

            TextureObject texture;
            texture.ID                          = textureFromFile(texturePath.C_Str(), directory);
            texture.type                        = typeID_;
            texture.path                        = texturePath.C_Str();

            textures.push_back(texture);
            texturesLoaded.push_back(texture);

        }

    }

    return textures;

}

uint32_t Model::textureFromFile(const char *path_, const std::string& directory_, bool gamma_) {

    std::string path = std::string(directory + '/' + path_);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
    
}


Model::~Model() {

    for (auto mesh : meshes) {
    
        delete mesh;
    
    }

}