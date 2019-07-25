/**
    Implementation the Mesh class

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         Mesh.cpp
    @brief        Implementation of the Mesh class
*/
#include "Mesh.hpp"
#include "OGL.hpp"
#include "ASSERT.cpp"


Mesh::Mesh(std::vector< BaseVertex >& vertices_, std::vector< uint32_t >& indices_, std::vector< TextureObject >& textures_, Shader shader_) 
    : vertices(vertices_), indices(indices_), textures(textures_), shader(shader_) {

    std::scoped_lock< std::mutex > lock(ogl::bufferGenerationMutex);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BaseVertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // vertex pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BaseVertex), (void*)0);

    // vertex nor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BaseVertex), (void*)offsetof(BaseVertex, nor));

    // vertex tex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BaseVertex), (void*)offsetof(BaseVertex, tex));

    // vertex tan
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BaseVertex), (void*)offsetof(BaseVertex, tan));

    // vertex bit
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(BaseVertex), (void*)offsetof(BaseVertex, bit));

    glBindVertexArray(0);

}

void Mesh::draw() {

    unsigned int diffuseNr      = 1;
    unsigned int specularNr     = 1;
    unsigned int normalNr       = 1;
    unsigned int heightNr       = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {

        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name;
        TEXTURE_TYPE type = textures[i].type;
        if (type == TT_DIFFUSE) {

            number = std::to_string(diffuseNr++);
            name = "texDiffuse";

        }
        else if (type == TT_SPECULAR) {

            number = std::to_string(specularNr++);
            name = "texSpecular";

        }
        else if (type == TT_NORMAL) {

            number = std::to_string(normalNr++);
            name = "texNormal";

        }
        else if (type == TT_HEIGHT) {

            number = std::to_string(heightNr++);
            name = "texHeight";

        }

        shader.setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);

    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast< GLsizei >(indices.size()), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

}

Mesh::~Mesh() {

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    logger::log(EVENT_LOG, "Successfully destroyed buffers of mesh");

}