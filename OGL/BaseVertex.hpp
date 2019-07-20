/**
    Defines the BaseVertex struct

    @author       D3PSI
    @version      0.0.1 02.12.2019

    @file         BaseVertex.hpp
    @brief        Definition of the BaseVertex struct
*/
#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <functional>

struct BaseVertex {

    glm::vec3 pos;
    glm::vec3 nor;
    glm::vec2 tex;
    glm::vec3 tan;
    glm::vec3 bit;

    /**
        Overload comparison-operator
    */
    bool operator==(const BaseVertex& otherVertex) const {

        return pos == otherVertex.pos && nor == otherVertex.nor && tex == otherVertex.tex && tan == otherVertex.tan && bit == otherVertex.bit;

    }

};

/**
    Expand standard namespace
*/
namespace std {

    /**
        Hash-function for vertex !!!This is some high level C++!!! (following recommended approach for hash-functions on cppreference.com's std::hash page)
    */
    template<  > struct hash< BaseVertex > {

        size_t operator()(BaseVertex const& vertex) const noexcept {

            return (std::hash< glm::vec3 >()(vertex.pos) ^
                (std::hash< glm::vec2 >()(vertex.tex)) << 1);

        }

    };

}